/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:36:01 by vcereced          #+#    #+#             */
/*   Updated: 2023/10/29 21:57:16 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *ft_parse_map_title(void)
{
	int		fd;
	char	*buffer;
	int		bytes;
	int		i;

	i = 1;
	bytes = 1;
	fd = open("./map_title/title.fdf", O_RDONLY);
	if (!fd)
		msg_error("CANNOT OPEN MAP TITLE");
	buffer= ft_calloc(1, BUFFER_SIZE);
	bytes = read(fd, buffer, BUFFER_SIZE);
	close(fd);
	if (bytes == -1 || bytes == 0)
	{
		free(buffer);
		ft_error("CANNOT READ MAP TITLE");
	}
	if (bytes < BUFFER_SIZE)
		buffer[bytes] = '\0';
	else
	{
		fd = open("./map_title/title.fdf", O_RDONLY);
		while (read(fd, buffer, BUFFER_SIZE) == BUFFER_SIZE)
			i++;
		bytes = i * BUFFER_SIZE;
		close(fd);
		free(buffer); //[1] Freed here
		buffer = ft_calloc(1, bytes); //[2] malloc Take care of this!!
		fd = open("./map_title/title.fdf", O_RDONLY);
		read(fd, buffer, bytes);
	}
	return (buffer);
}

void	ft_draw_sq(mlx_image_t* img, t_data * data, int x1, int y1)
{
	int x;
	int y;
	int last_x;
	int last_y;
	/*EXPERIMENTAL GAP*/
	last_y = y1 + ((fabs)(HEIGHT_IMG_TITLE / data->title.width)) + (data->title.row *10);
	last_x = x1 + ((fabs)(WIDTH_IMG_TITLE / data->title.length)) + (data->title.column * 10);
	y =y1+ (data->title.row *10);
	/*NORMAL*/
	//last_y = y1 + ((fabs)(HEIGHT_IMG_TITLE / data->title.width));
	//last_x = x1 + ((fabs)(WIDTH_IMG_TITLE / data->title.length));
	//y =y1;
	while(y <= last_y)
	{
		/*EPERIMAENTAL*/
		x =x1 + (data->title.column * 10);
		/*NORMAL*/
		//x =x1;
		while(x <= last_x)//aqui empieza cada cuadro
		{
			int z;
			z = 0;
			//if (!(y == last_y) && !(x == last_x))
			//	mlx_put_pixel(img, x, y, set_color(y + data->plus));
			while(z <= (WIDTH*0.01))//genera profundidad HARDCODED
			{
				mlx_put_pixel(img, x+z, y+z, set_color(y + data->plus));
				if(y == y1+ (data->title.row *10))
					mlx_put_pixel(img, x+z, y+z, 0x000000FF);
			//	if (x == x1 && y != last_y-1 && z != last_x-1)
			//		mlx_put_pixel(img, x+z, y+z, 0x000000FF);
				if (x == x1 + (data->title.column * 10))
					mlx_put_pixel(img, x+z, y+z, 0x000000FF);
				if (x == last_x &&y == last_y)
					mlx_put_pixel(img, x+z, y+z, 0x000000FF);
				z++;
			}
			
			if (y == last_y)
			{
				mlx_put_pixel(img, x+z, y+z, 0x000000FF);
				mlx_put_pixel(img, x, y, 0x000000FF);
			}
			if (x == last_x)
			{
				mlx_put_pixel(img, x+z, y+z, 0x000000FF);
				mlx_put_pixel(img, x, y, 0x000000FF);
				
			}
			//mlx_put_pixel(img, x, y, set_color(y + data->plus));
			x++;
		}
	
		y++;
	}
	
}

void draw_square(t_data * data, mlx_image_t* img)
{
	int x1;
	int y1;

	x1 = data->title.column * ((fabs)((WIDTH_IMG_TITLE) / data->title.length));
	y1 = data->title.row * ((fabs)((HEIGHT_IMG_TITLE) / data->title.width));
	ft_draw_sq(img, data, x1, y1);
}

void draw_title(t_data * data, mlx_image_t* img)
{

	int row;
	int column;
	
	row = 0;
	data->title.row = row;
	while(data->title.arr[row]&& (row < data->title.width))
	{
		column = 0;
		data->title.column = column;
		while(data->title.arr[row][column] && (column < data->title.length))
		{
			if(data->title.arr[row][column] == '1')
				draw_square(data, img);
			column++;
			data->title.column = column;
			
		}
		row++;
		data->title.row = row;
	}
}

char **ft_skip_sp_arr(char **arr)
{
	int i;
	int j;
	int n;

	char *buffer;
	int len;
	
	len = 0;
	i = 0;
	while(arr[0][i])
	{
		if(ft_isdigit(arr[0][i]))
			len++;
		i++;
	}
	i = 0;
	while(arr[i])
	{
		j=0;
		n = 0;
		buffer = (char *)calloc(len + 1,  1);
		while (arr[i][n])
		{
			if(ft_isdigit(arr[i][n]))
			buffer[j++] = arr[i][n];
			n++;
		}
		free(arr[i]);
		arr[i] = buffer;
		i++;
	}
	return(arr);
}

void draw(void *d)
{
	int i;
	static int n;
	
	i = 255;
	t_data *data = (t_data *)d;

	data->plus += 15 ;
	if (data->plus >= ((HEIGHT_IMG_TITLE)*3))
		data->plus = 0;
	
	if (mlx_is_key_down(data->mlx, MLX_KEY_ENTER))
		data->flag = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if(data->flag == 0)
		draw_title(data, data->img);
	if (data->flag == 1)
	{
		data->startimg->enabled = 0;
		n+=2;
		if(n >400)
		{
			ft_memset(data->img->pixels, 0,WIDTH * HEIGHT * sizeof(int32_t));
			ft_memset(data->img2->pixels, 0,WIDTH_IMG_TITLE_MAP * HEIGTH_IMG_TITLE_MAP * sizeof(int32_t));
			ft_memset(data->img3->pixels, 0 ,WIDTH_IMG_TITLE_MAP * HEIGTH_IMG_TITLE_MAP * sizeof(int32_t));
		}
		else if (n > 80)
		{
			if (n <255)
			{
				ft_memset(data->img3->pixels, 255-n ,WIDTH_IMG_TITLE_MAP * HEIGTH_IMG_TITLE_MAP * sizeof(int32_t));
				ft_memset(data->img2->pixels, 255-n,WIDTH_IMG_TITLE_MAP * HEIGTH_IMG_TITLE_MAP * sizeof(int32_t));
				
			}
				
			//memset(data->img->pixels, 255-n,WIDTH * HEIGHT * sizeof(int32_t));
		}
			
		else if (n <=80)
		{
		ft_memset(data->img3->pixels, 0 ,WIDTH_IMG_TITLE_MAP * HEIGTH_IMG_TITLE_MAP * sizeof(int32_t));
		data->map.zoom += 0.1;
		ft_memset(data->img2->pixels, 0,WIDTH_IMG_TITLE_MAP * HEIGTH_IMG_TITLE_MAP * sizeof(int32_t));
		draw_title_map(data, data->img2);
		draw_title(data, data->img);	
		}
		
	}

	
}


//map de titulo NO CHEKEA ONLY PARSE!!!
void	ft_phase_1(t_data *data, mlx_t* mlx)
{
	data->map.zoom = 0.0; 
	data->plus = 0;
	data->mlx = mlx;
	mlx_image_t* img = mlx_new_image(mlx, WIDTH_IMG_TITLE, HEIGHT_IMG_TITLE);
	mlx_image_t* img2 = mlx_new_image(mlx, WIDTH_IMG_TITLE_MAP, HEIGTH_IMG_TITLE_MAP);
	mlx_image_t* img3 = mlx_new_image(mlx, WIDTH, HEIGHT);
	data->img = img;
	data->img2 = img2;
	data->img3 = img3;
	mlx_texture_t *start;
	mlx_image_t *startimg;
	
	start = mlx_load_png("./map_title/start2.png");
	startimg = mlx_texture_to_image(data->mlx, start);
	data->startimg = startimg;
	//memset(startimg->pixels, 255, startimg->width * startimg->height * sizeof(int32_t));
	mlx_image_to_window(data->mlx, startimg, (WIDTH / 2) -(startimg->width/2), (HEIGHT/2) - ((startimg->height/2)));
	//mlx_image_t* img = mlx_new_image(mlx, 100, 100);
	char *buffer_str;
	
	buffer_str = ft_parse_map_title();
	data->title.arr = ft_split(buffer_str, '\n');
	data->title.arr = ft_skip_sp_arr(data->title.arr);
	free(buffer_str);
	data->title.length = ft_strlen(data->title.arr[0]);
	data->title.width = ft_arrlen(data->title.arr);

	//draw_title(data, img);

	draw_title_map(data, img2);
	//memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	//memset(img2->pixels, 255,WIDTH_IMG_TITLE_MAP * HEIGTH_IMG_TITLE_MAP * sizeof(int32_t));
	//memset(img3->pixels, 255,WIDTH * HEIGHT * sizeof(int32_t));
	mlx_image_to_window(mlx, img3, 0, 0);
	mlx_image_to_window(mlx, img, (WIDTH / 2) -(WIDTH_IMG_TITLE/2), (HEIGHT *0.03));
	mlx_image_to_window(mlx, img2, (WIDTH / 2) -(WIDTH_IMG_TITLE_MAP/2), 0);
	mlx_loop_hook(mlx, draw, data);
	
	mlx_loop(mlx);
}   