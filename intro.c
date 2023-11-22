/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:36:01 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/22 13:07:10 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_cpy(char *buffer)
{
	int	fd;
	int	i;

	i = 1;
	fd = open("./map_title/title.fdf", O_RDONLY);
	while (read(fd, buffer, BUFFER_SIZE) == BUFFER_SIZE)
		i++;
	close(fd);
	free(buffer);
	buffer = ft_calloc(1, i * BUFFER_SIZE);
	fd = open("./map_title/title.fdf", O_RDONLY);
	read(fd, buffer, i * BUFFER_SIZE);
	close(fd);
	return (buffer);
}

char	*ft_cpy_title(void)
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
	buffer = ft_calloc(1, BUFFER_SIZE);
	bytes = read(fd, buffer, BUFFER_SIZE);
	close(fd);
	if (bytes <= 0)
	{
		free(buffer);
		buffer = NULL;
		ft_error("CANNOT READ MAP TITLE");
	}
	else
		buffer = ft_cpy(buffer);
	return (buffer);
}

char	*ft_parse_title(t_data *data)
{
	char	*buffer;

	buffer = ft_cpy_title();
	data->title.arr = ft_split(buffer, '\n');
	data->title.arr = ft_skip_sp_arr(data->title.arr);
	free(buffer);
	data->title.length = ft_strlen(data->title.arr[0]);
	data->title.heigth = ft_arrlen(data->title.arr);
	return (buffer);
}

void	ft_transition(int *n, t_data *data)
{
	(*n) += 1;
	if (*n == 155)
	{
		data->img[MAP_INTRO]->enabled = 0;
		data->img[TITLE_INTRO]->enabled = 0;
		data->phase = 1;
	}
	else if ((*n) == 150)
		ft_memset(data->img[TITLE_INTRO]->pixels, 0, WIDTH_IMG_TITLE * HEIGHT_IMG_TITLE * sizeof(int32_t));
	else if ((*n) > 30 && (*n) < 120)
		ft_memset(data->img[MAP_INTRO]->pixels, 255 - ((*n) * 2), WIDTH_IMG_TITLE_MAP * HEIGTH_IMG_TITLE_MAP * sizeof(int32_t));
	else if ((*n) < 30)
	{
		data->title.boom += 0.2;
		ft_memset(data->img[MAP_INTRO]->pixels, 0, WIDTH_IMG_TITLE_MAP * HEIGTH_IMG_TITLE_MAP * sizeof(int32_t));
		draw_title(data);
		draw_title_map(data);
	}
}

void	ft_intro_loop(t_data	*data)
{
	static int	n;

	data->title.color_up += 15 ;
	if (data->title.color_up >= ((HEIGHT_IMG_TITLE) * 3))
		data->title.color_up = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ENTER))
		data->title.flag = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);//falta funcion pa liberar todo
	if (data->title.flag == 0)
	{
		if (ft_changed_resolution(data))
		{
			mlx_resize_image(data->img[TITLE_INTRO], (int)(WIDTH_IMG_TITLE), (int)(HEIGHT_IMG_TITLE));
			mlx_resize_image(data->img[MAP_INTRO], WIDTH_IMG_TITLE_MAP, HEIGTH_IMG_TITLE_MAP);
			ft_memset(data->img[TITLE_INTRO]->pixels, 0, (int)(WIDTH_IMG_TITLE)*(int)(HEIGHT_IMG_TITLE) * sizeof(int32_t));
			ft_memset(data->img[MAP_INTRO]->pixels, 0, WIDTH_IMG_TITLE_MAP * HEIGTH_IMG_TITLE_MAP * sizeof(int32_t));
			draw_title_map(data);
		}
		draw_title_map(data);
		draw_title(data);
		ft_draw_start_texture(HEIGTH_IMG_TITLE_MAP * 0.04, WIDTH_IMG_TITLE_MAP * 0.3, (WIDTH / 2), data);
	}
	if (data->title.flag == 1)
		ft_transition(&n, data);
}
