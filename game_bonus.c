/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:18:54 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/18 19:18:32 by dgarizad         ###   ########.fr       */
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
}

void    ft_hook(void *param)
{
	t_data  *data;
	double	start;
	double	end;
	double	elapsed;

	data = param;
	start = (double)clock() / CLOCKS_PER_SEC;
	if (data->map.mlx->width != data->map.width * data->map.ppc || \
	data->map.mlx->height != data->map.height * data->map.ppc)
		ft_fix_images(data);
	ray_bang(data);
	end = (double)clock() / CLOCKS_PER_SEC;
	if (end - start < 0.016)
	{
		elapsed = 0.016 - (end - start);
		usleeºp(elapsed * 1000000);
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
	data->map.mlx = mlx_init(WIDTH, HEIGHT, \
	"Cub3D", true);
	data->map.img3d = mlx_new_image(data->map.mlx,data->map.width * data->map.ppc, \
	data->map.height * data->map.ppc);
	data->map.mini = mlx_new_image(data->map.mlx, data->map.width * data->map.minimap_scale, \
	data->map.height * data->map.minimap_scale);
	ft_memset(data->map.mini->pixels, 0xC0, data->map.mini->width * \
	data->map.mini->height * 4);
	mlx_image_to_window(data->map.mlx, data->map.img3d, 0, 0);
	mlx_image_to_window(data->map.mlx, data->map.mini, \
	data->map.width * data->map.ppc - data->map.mini->width, data->map.height * data->map.ppc \
	- data->map.mini->height);  
}

void	ft_game(t_data *data)
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

