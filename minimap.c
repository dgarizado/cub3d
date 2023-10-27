/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:18:54 by dgarizad          #+#    #+#             */
/*   Updated: 2023/10/26 23:10:52 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_movement_calc(t_data *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && \
	data->map.map_aclean[data->player.y][data->player.x + 1] != '1')
	{
		data->player.flag = true;
		data->player.x += 1;
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && \
	data->map.map_aclean[data->player.y][data->player.x - 1] != '1')
	{
		data->player.flag = true;
		data->player.x -= 1;
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && \
	data->map.map_aclean[data->player.y - 1][data->player.x] != '1')
	{
		data->player.flag = true;
		data->player.y -= 1;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && \
	data->map.map_aclean[data->player.y + 1][data->player.x] != '1')
	{
		data->player.flag = true;
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
		data->map.img->instances[0].y += 12;
		data->map.minimap.img[PLAYER]->instances[0].y -= 20;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && data->player.flag == true)
	{
		data->map.img->instances[0].y -= 12;
		data->map.minimap.img[PLAYER]->instances[0].y += 20;
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && data->player.flag == true)
	{
		data->map.img->instances[0].x += 12;
		data->map.minimap.img[PLAYER]->instances[0].x -= 20;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && data->player.flag == true)
	{
		data->map.img->instances[0].x -= 12;
		data->map.minimap.img[PLAYER]->instances[0].x += 20;	
	}
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->map.mlx);
}

void	ft_hook(void *param)
{
	t_data *data;

	data = param;
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
			if (data->map.map_aclean[i][j] == '0' || data->map.map_aclean[i][j] == 'N')
				ft_paintblock(data, j, i, 0x0000FF);
			if (data->map.map_aclean[i][j] == ' ')
				ft_paintblock(data, j, i, 00);
			j++;
		}
		i++;
	}
}

void	ft_minimap(t_data *data)
{
	data->map.mlx = mlx_init(data->map.width*40, data->map.height*40, "Cub3D", true);
	printf("width = %d, height = %d\n", data->map.width*40, data->map.height*40);
	ft_load_minisprites(data);
	data->map.img = mlx_new_image(data->map.mlx, data->map.width*12, data->map.height*12);
	data->player.point = mlx_new_image(data->map.mlx, 4, 4);
	ft_memset(data->map.img->pixels, 0xC0, data->map.img->width * data->map.img->height*4);
	ft_memset(data->player.point->pixels, 0xFF, data->player.point->width * data->player.point->height*4);
	ft_draw_minimap(data);
	mlx_image_to_window(data->map.mlx, data->map.img,data->map.width*40 - data->map.img->width, data->map.height*40 - data->map.img->height);
	mlx_image_to_window(data->map.mlx, data->player.point, 1268, 532);
	ft_draw_map(data);
	mlx_key_hook(data->map.mlx, &ft_keyhook, data);
	mlx_loop_hook(data->map.mlx, ft_hook, data);
	mlx_loop(data->map.mlx);
	mlx_terminate(data->map.mlx);
}