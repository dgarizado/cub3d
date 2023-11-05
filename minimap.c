/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:18:54 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/05 16:53:04 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_movement_calc(t_data *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && \
	data->map.map_aclean[data->player.y][data->player.x + 1] != '1')
	{
		data->player.flag = true;
		mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0x00000FF);	
		data->player.x += 1;
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && \
	data->map.map_aclean[data->player.y][data->player.x - 1] != '1')
	{
		data->player.flag = true;
		mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0x00000FF);
		data->player.x -= 1;
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && \
	data->map.map_aclean[data->player.y - 1][data->player.x] != '1')
	{
		data->player.flag = true;
		mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0x00000FF);
		data->player.y -= 1;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && \
	data->map.map_aclean[data->player.y + 1][data->player.x] != '1')
	{
		data->player.flag = true;
		mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0x00000FF);
		data->player.y += 1;
	}
	return (0);
}


void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = param;
	data->player.flag = false;
	ft_movement_calc(data, keydata);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && data->player.flag == true)
	{
		// data->map.img->instances[0].y += 12;
		mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0xFF000FF);
		// ray_charles(data);
		// ray_bang(data);
		// data->map.minimap.img[PLAYER]->instances[0].y -= 20;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && data->player.flag == true)
	{
		// data->map.img->instances[0].y -= 12;
		// data->map.minimap.img[PLAYER]->instances[0].y += 20;
		mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0xFF000FF);
		// ray_charles(data);
		// ray_bang(data);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && data->player.flag == true)
	{
		// data->map.img->instances[0].x += 12;
		// data->map.minimap.img[PLAYER]->instances[0].x -= 20;
		// data->player.point->instances[0].x -= 12;
		mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0xFF000FF);
		data->player.angle -= FOV/data->map.width*PPC;
		// ray_bang(data);

		// ray_charles(data);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && data->player.flag == true)
	{
		// data->map.img->instances[0].x -= 12;
		// data->map.minimap.img[PLAYER]->instances[0].x += 20;	
		// data->player.point->instances[0].x += 12;
		mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0xFF000FF);
		data->player.angle += FOV/data->map.width*PPC;
		// ray_bang(data);

		// ray_charles(data);
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		data->player.angle -= 1;
		rotate_victor(&data->player.vdir, -1);
		rotate_victor(&data->player.plane, -1);
		// ray_charles(data);
		// ray_bang(data);
	}
	// if (keydata.key == MLX_KEY_RIGHT)
	// {
	// 	data->player.angle += 1;
	// 	rotate_victor(&data->player.vdir, 1);
	// 	rotate_victor(&data->player.plane, 1);
	// 	// ray_charles(data);
	// 	// ray_bang(data);
	// }
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->map.mlx);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		data->map.img->instances[0].enabled = !data->map.img->instances[0].enabled;
	}
}


void	ft_hook2(void *param)
{
	t_data *data;

	data = param;
	if (mlx_is_key_down(data->map.mlx, MLX_KEY_V))
	{
		data->map.img->instances[0].enabled = !data->map.img->instances[0].enabled;
	}
	if (mlx_is_key_down(data->map.mlx, MLX_KEY_RIGHT))
	{
		data->player.angle += 1;
		rotate_victor(&data->player.vdir, 11);
		rotate_victor(&data->player.plane, 11);
	}
	if (mlx_is_key_down(data->map.mlx, MLX_KEY_LEFT))
	{
		data->player.angle -= 1;
		rotate_victor(&data->player.vdir, -11);
		rotate_victor(&data->player.plane, -11);
	}
	if (mlx_is_key_down(data->map.mlx, MLX_KEY_W))
	{
		
		if (data->map.map_aclean[data->player.y - 1][data->player.x] != '1')
		{
			data->player.flag = true;
			mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0x00000FF);
			data->player.y -= 1;
			mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0xFF000FF);
		}
	}
	if (mlx_is_key_down(data->map.mlx, MLX_KEY_S))
	{
		if (data->map.map_aclean[data->player.y + 1][data->player.x] != '1')
		{
			data->player.flag = true;
			mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0x00000FF);
			data->player.y += 1;
			mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0xFF000FF);
		}
	}
	if (mlx_is_key_down(data->map.mlx, MLX_KEY_A))
	{
		if (data->map.map_aclean[data->player.y][data->player.x - 1] != '1')
		{
			data->player.flag = true;
			mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0x00000FF);
			data->player.x -= 1;
			mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0xFF000FF);
		}
	}
	if (mlx_is_key_down(data->map.mlx, MLX_KEY_D))
	{
		if (data->map.map_aclean[data->player.y][data->player.x + 1] != '1')
		{
			data->player.flag = true;
			mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0x00000FF);	
			data->player.x += 1;
			mlx_put_pixel(data->map.img, (data->player.x)*12 +6, (data->player.y)*12 +6, 0xFF000FF);
		}
	}
	int mx;
	int my;
	mlx_get_mouse_pos(data->map.mlx, &mx, &my);
	if (mx > data->player.mouse_x && data->player.mouse_x > 0 && data->player.mouse_x < data->map.width*PPC )
	{
		data->player.angle += 1;
		rotate_victor(&data->player.vdir, 5);
		rotate_victor(&data->player.plane, 5);
	}
	if (mx < data->player.mouse_x && data->player.mouse_x < data->map.width*PPC && data->player.mouse_x > 0)
	{
		data->player.angle -= 1;
		rotate_victor(&data->player.vdir, -5);
		rotate_victor(&data->player.plane, -5);
	}
	if (my > data->player.mouse_y && data->player.mouse_y > 0 && data->player.mouse_y < data->map.height*PPC)
	{
		data->player.vertical += 70;
	}
	if (my < data->player.mouse_y && data->player.mouse_y < data->map.height*PPC && data->player.mouse_y > 0)
	{
		data->player.vertical -= 70;
	}
	data->player.mouse_y = my;
	data->player.mouse_x = mx;
	if (data->player.sprites.pistol_bang->instances[0].enabled == true)
		data->player.sprites.pistol_bang->instances[0].enabled = false;
	if (mlx_is_mouse_down(data->map.mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		data->player.sprites.pistol_bang->instances[0].enabled = true;
	}
		
}



void	ft_hook(void *param)
{
	t_data *data;

	data = param;
	ray_bang(data);
	
	
}

void ft_draw_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	ft_print_array(data->map.map_aclean);
	while (data->map.map_aclean[i])
	{
		j = 0;
		while (data->map.map_aclean[i][j])
		{
			if (data->map.map_aclean[i][j] == '1')
				mlx_image_to_window(data->map.mlx, data->map.minimap.img[WALL], j*20+200, i*20+200);
			if (data->map.map_aclean[i][j] == '0')
				mlx_image_to_window(data->map.mlx, data->map.minimap.img[EMPTY], j*20+200, i*20+200);
			if (data->map.map_aclean[i][j] == 'N')
			{
				mlx_image_to_window(data->map.mlx, data->map.minimap.img[EMPTY], j*20+200, i*20+200);
				mlx_image_to_window(data->map.mlx, data->map.minimap.img[PLAYER], j*20+200, i*20+200);
				data->map.minimap.img[PLAYER]->instances[0].z = data->map.width* data->map.height;
			}
			if (data->map.map_aclean[i][j] == ' ')
				mlx_image_to_window(data->map.mlx, data->map.minimap.img[SPACE], j*20+200, i*20+200);
			j++;

		}
		i++;
	}
}
void ft_paintblock(t_data *data, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	x = x * 12;
	y = y * 12;
	while(i < 12)
	{
		j = 0;
		while(j < 12)
		{
			mlx_put_pixel(data->map.img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
void ft_draw_minimap(t_data *data)
{
	int	i;
	int	j;
	i = 0;
	while (data->map.map_aclean[i])
	{
		j = 0;
		while (data->map.map_aclean[i][j])
		{
			if (data->map.map_aclean[i][j] == '0' || \
			data->map.map_aclean[i][j] == 'N' || \
			data->map.map_aclean[i][j] == 'S' || \
			data->map.map_aclean[i][j] == 'W' || \
			data->map.map_aclean[i][j] == 'E')
				ft_paintblock(data, j, i, 0x0000FF);
			if (data->map.map_aclean[i][j] == ' ')
				ft_paintblock(data, j, i, 0x000000);
			j++;
		}
		i++;
	}
}


void ft_draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	err = dx - dy;
	if (x1 < x2)
		sx = 1;
	else
		sx = -1;
	if (y1 < y2)
		sy = 1;
	else
		sy = -1;
	while (x1 != x2 || y1 != y2)
	{
		if (x1 >= 0 && x1 < (int)img->width && y1 >= 0 && y1 < (int)img->height)
			mlx_put_pixel(img, x1, y1, color);
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}
void	ft_minimap(t_data *data)
{
	data->map.mlx = mlx_init(data->map.width*PPC, data->map.height*PPC, "Cub3D", true);
	printf("width = %d, height = %d\n", data->map.width*PPC, data->map.height*PPC);
	data->player.img3d = mlx_new_image(data->map.mlx,data->map.width*PPC , data->map.height*PPC);
	data->player.plane.x = 0;
	data->player.plane.y = 0.66;
	mlx_get_mouse_pos(data->map.mlx, &data->player.mouse_x, &data->player.mouse_y);
	mlx_image_to_window(data->map.mlx, data->player.img3d, 0, 0);
	ft_load_minisprites(data);
	data->map.img = mlx_new_image(data->map.mlx, data->map.width*12, data->map.height*12);
	ft_memset(data->map.img->pixels, 0xC0, data->map.img->width * data->map.img->height*4);
	ft_draw_minimap(data);
	mlx_image_to_window(data->map.mlx, data->map.img,data->map.width*PPC - data->map.img->width, data->map.height*PPC - data->map.img->height);
	mlx_image_to_window(data->map.mlx, data->player.sprites.pistol_bang, data->map.width*PPC/2 - data->player.sprites.pistol_bang->width/2, data->map.height*PPC - data->player.sprites.pistol_bang->height);
	data->player.sprites.pistol_bang->instances[0].enabled = false;
	mlx_image_to_window(data->map.mlx, data->player.sprites.pistol_img, data->map.width*PPC/2 - data->player.sprites.pistol_img->width/2, data->map.height*PPC - data->player.sprites.pistol_img->height);
	mlx_put_pixel(data->map.img, data->player.x*12 + 6, data->player.y*12 +6, 0xFF00FF);
	mlx_key_hook(data->map.mlx, ft_keyhook, data);
	mlx_loop_hook(data->map.mlx, ft_hook, data);
	mlx_loop_hook(data->map.mlx, ft_hook2, data);
	// ray_charles(data);
	mlx_loop(data->map.mlx);
	mlx_terminate(data->map.mlx);
}
