/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:18:54 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/16 18:07:55 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

void ft_draw_minimap(t_data *data);

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	double	next_x;
	double	next_y;

	data = param;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->map.mlx);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		data->map.mini->instances[0].enabled ^= true;
	}
	if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
	{
		next_x = data->player.pos.x + data->player.vdir.x;
		next_y = data->player.pos.y + data->player.vdir.y;
		if (data->map.map_aclean[(int)next_y][(int)next_x] == 'D' || \
		data->map.map_aclean[(int)next_y][(int)next_x] == 'O')
		{
			data->map.map_aclean[(int)next_y][(int)next_x] = '0';
			ft_draw_minimap(data);
		}
	}
}

void	ft_hook2(void *param)
{
	t_data	*data;

	data = param;
	verticals_w(data);
	verticals_s(data);
	laterals_a(data);
	laterals_d(data);
	mouse(data);
	if (mlx_is_mouse_down(data->map.mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		data->sprites[PISTOL]->instances[0].enabled = false;
		data->sprites[PISTOL_BANG]->instances[0].enabled = true;
	}
}

void ft_fix_images(t_data *data)
{
	mlx_resize_image(data->map.img3d, data->map.mlx->width, \
	data->map.mlx->height);
	data->map.ppc = data->map.mlx->width / data->map.width;
	data->sprites[PISTOL]->instances[0].x = data->map.mlx->width / 2 - \
	data->sprites[PISTOL]->width/2;
	data->sprites[PISTOL]->instances[0].y = data->map.mlx->height - \
	data->sprites[PISTOL]->height;
	data->sprites[PISTOL_BANG]->instances[0].x = data->map.mlx->width / 2 - \
	data->sprites[PISTOL_BANG]->width/2 + 10;
	data->sprites[PISTOL_BANG]->instances[0].y = data->map.mlx->height - \
	data->sprites[PISTOL_BANG]->height + 10;
	data->map.mini->instances[0].x = data->map.mlx->width - \
	data->map.mini->width;
	data->map.mini->instances[0].y = data->map.mlx->height - \
	data->map.mini->height;
}

void    ft_hook(void *param)
{
	t_data  *data;
	double	start;
	double	end;
	double	elapsed;

	data = param;
	start = (double)clock() / CLOCKS_PER_SEC;
	//chech if mlx window was resized 
	if (data->map.mlx->width != data->map.width * data->map.ppc || \
	data->map.mlx->height != data->map.height * data->map.ppc)
		ft_fix_images(data);
	ray_bang(data);
	if (mlx_is_key_down(data->map.mlx, MLX_KEY_RIGHT))
	{
		rotate_victor(&data->player.vdir, 1);
		rotate_victor(&data->player.plane, 1);
	}
	if (mlx_is_key_down(data->map.mlx, MLX_KEY_LEFT))
	{
		rotate_victor(&data->player.vdir, -1);
		rotate_victor(&data->player.plane, -1);
	}
	end = (double)clock() / CLOCKS_PER_SEC;
	if (end - start < 0.016)
	{
		elapsed = 0.016 - (end - start);
		usleep(elapsed * 1000000);
	} 	
}

void ft_paintblock(t_data *data, int x, int y, u_int32_t color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	x = x * data->map.minimap_scale;
	y = y * data->map.minimap_scale;
	while(i < data->map.minimap_scale)
	{
		j = 0;
		while(j < data->map.minimap_scale)
		{
			mlx_put_pixel(data->map.mini, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void ft_draw_minimap(t_data *data)
{
	int i;
	int j;
	
	i = 0;
	ft_memset(data->map.mini->pixels, 0xC0, data->map.mini->width * \
	data->map.mini->height * 4);
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
			{
				data->map.map_aclean[i][j] = '0';
				ft_paintblock(data, j, i, 0x0000FF);
			}
			if (data->map.map_aclean[i][j] == ' ')
				ft_paintblock(data, j, i, 0x000000);
			if (data->map.map_aclean[i][j] == 'D')
				ft_paintblock(data, j, i, 0x882200F0);
			if (data->map.map_aclean[i][j] == 'O')
				ft_paintblock(data, j, i, 0xFFFF00FF);
			j++;
		}
		i++;
	}
	mlx_put_pixel(data->map.mini, data->player.pos.x*data->map.minimap_scale , \
	data->player.pos.y*data->map.minimap_scale , 0xFF00FF);
	mlx_put_pixel(data->map.mini, data->player.pos.x*data->map.minimap_scale + 10, \
	data->player.pos.y*data->map.minimap_scale , 0xFF0000FF);//This is Steve's position
	printf("x = %f, y = %f\n", data->player.pos.x, data->player.pos.y);
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

/**
 * @brief Create a mlx_image_t object
 * Creates the render image for the game and
 * the minimap image.
 * @param data 
 */
void    ft_init_graphics(t_data *data)
{
	data->map.ppc = WIDTH / data->map.width;
	data->map.minimap_scale = 340/data->map.width;
	if (140 / data->map.height < data->map.minimap_scale)
		data->map.minimap_scale = 140 / data->map.height;
	if (data->map.minimap_scale < 1)
		data->map.minimap_scale = 1;
	printf("ppc = %d\n", data->map.ppc);
	printf("data->map.minimap_scale = %d\n", data->map.minimap_scale);
	printf("mini map width = %d\n", data->map.width * data->map.minimap_scale);
	printf("mini map height = %d\n", data->map.height * data->map.minimap_scale);
	printf("mini map height scale = %d\n", 140/data->map.width);
	data->map.mlx = mlx_init(WIDTH, HEIGHT, \
	"Cub3D", true);
	data->map.img3d = mlx_new_image(data->map.mlx,data->map.width * data->map.ppc, \
	data->map.height * data->map.ppc);
	data->map.mini = mlx_new_image(data->map.mlx, data->map.width * data->map.minimap_scale, \
	data->map.height * data->map.minimap_scale);
	mlx_image_to_window(data->map.mlx, data->map.img3d, 0, 0);
	mlx_image_to_window(data->map.mlx, data->map.mini, \
	data->map.width * data->map.ppc - data->map.mini->width, data->map.height * data->map.ppc \
	- data->map.mini->height);  
}

void    ft_game(t_data *data)
{
    ft_init_graphics(data);
    ft_load_minisprites(data);
    ft_draw_minimap(data);
	mlx_set_cursor_mode(data->map.mlx, MLX_MOUSE_HIDDEN);
	mlx_key_hook(data->map.mlx, ft_keyhook, data);
    mlx_loop_hook(data->map.mlx, ft_hook, data);
    mlx_loop_hook(data->map.mlx, ft_hook2, data);
    mlx_loop(data->map.mlx);
    mlx_terminate(data->map.mlx);
}

