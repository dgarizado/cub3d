/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:23:06 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/24 16:43:18 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verticals_w(t_data *data)
{
	double	next_x;
	double	next_y;

	if (mlx_is_key_down(data->map.mlx, MLX_KEY_W))
	{
		next_x = data->player.pos.x + data->player.vdir.x * MOVE_SPEED;
		if (data->map.map_aclean[(int)data->player.pos.y][(int)next_x] != '1')
		{
			mlx_put_pixel(data->map.mini, (data->player.pos.x) \
			* data->map.minimap_scale, \
			(data->player.pos.y) * data->map.minimap_scale, 0x00000FF);
			data->player.pos.x = next_x;
		}
		next_y = data->player.pos.y + data->player.vdir.y * MOVE_SPEED;
		if (data->map.map_aclean[(int)next_y][(int)data->player.pos.x] != '1')
		{
			mlx_put_pixel(data->map.mini, (data->player.pos.x) * \
			data->map.minimap_scale, \
			(data->player.pos.y) * data->map.minimap_scale, 0x00000FF);
			data->player.pos.y = next_y;
		}
		mlx_put_pixel(data->map.mini, (data->player.pos.x) * \
		data->map.minimap_scale, \
		(data->player.pos.y) * data->map.minimap_scale, 0xFF000FF);
	}
}

void	verticals_s(t_data *data)
{
	double	next_x;
	double	next_y;

	if (mlx_is_key_down(data->map.mlx, MLX_KEY_S))
	{
		next_x = data->player.pos.x - data->player.vdir.x * MOVE_SPEED;
		if (data->map.map_aclean[(int)data->player.pos.y][(int)next_x] != '1')
		{
			mlx_put_pixel(data->map.mini, (data->player.pos.x) * \
			data->map.minimap_scale, \
			(data->player.pos.y) * data->map.minimap_scale, 0x00000FF);
			data->player.pos.x = next_x;
		}
		next_y = data->player.pos.y - data->player.vdir.y * MOVE_SPEED;
		if (data->map.map_aclean[(int)next_y][(int)data->player.pos.x] != '1')
		{
			mlx_put_pixel(data->map.mini, (data->player.pos.x) * \
			data->map.minimap_scale, \
			(data->player.pos.y) * data->map.minimap_scale, 0x00000FF);
			data->player.pos.y = next_y;
		}
		mlx_put_pixel(data->map.mini, (data->player.pos.x) * \
		data->map.minimap_scale, \
		(data->player.pos.y) * data->map.minimap_scale, 0xFF000FF);
	}
}

void	laterals_a(t_data *data)
{
	double	next_x;
	double	next_y;

	if (mlx_is_key_down(data->map.mlx, MLX_KEY_A))
	{
		next_x = data->player.pos.x - data->player.plane.x * MOVE_SPEED;
		if (data->map.map_aclean[(int)data->player.pos.y][(int)next_x] != '1')
		{
			mlx_put_pixel(data->map.mini, (data->player.pos.x) * \
			data->map.minimap_scale, \
			(data->player.pos.y) * data->map.minimap_scale, 0x00000FF);
			data->player.pos.x = next_x;
		}
		next_y = data->player.pos.y - data->player.plane.y * MOVE_SPEED;
		if (data->map.map_aclean[(int)next_y][(int)data->player.pos.x] != '1')
		{
			mlx_put_pixel(data->map.mini, (data->player.pos.x) * \
			data->map.minimap_scale, \
			(data->player.pos.y) * data->map.minimap_scale, 0x00000FF);
			data->player.pos.y = next_y;
		}
		mlx_put_pixel(data->map.mini, (data->player.pos.x) * \
			data->map.minimap_scale, \
			(data->player.pos.y) * data->map.minimap_scale, 0xFF000FF);
	}
}

void	laterals_d(t_data *data)
{
	double	next_x;
	double	next_y;

	if (mlx_is_key_down(data->map.mlx, MLX_KEY_D))
	{
		next_x = data->player.pos.x + data->player.plane.x * MOVE_SPEED;
		if (data->map.map_aclean[(int)data->player.pos.y][(int)next_x] != '1')
		{
			mlx_put_pixel(data->map.mini, (data->player.pos.x) * \
			data->map.minimap_scale, \
			(data->player.pos.y) * data->map.minimap_scale, 0x00000FF);
			data->player.pos.x = next_x;
		}
		next_y = data->player.pos.y + data->player.plane.y * MOVE_SPEED;
		if (data->map.map_aclean[(int)next_y][(int)data->player.pos.x] != '1')
		{
			mlx_put_pixel(data->map.mini, (data->player.pos.x) * \
			data->map.minimap_scale, \
			(data->player.pos.y) * data->map.minimap_scale, 0x00000FF);
			data->player.pos.y = next_y;
		}
		mlx_put_pixel(data->map.mini, (data->player.pos.x) * \
		data->map.minimap_scale, \
		(data->player.pos.y) * data->map.minimap_scale, 0xFF000FF);
	}
}

void	mouse(t_data *data)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(data->map.mlx, &x, &y);
	if (x > data->player.mouse_x && data->player.mouse_x > 0 \
	&& data->player.mouse_x < data->map.width * data->map.ppc)
	{
		rotate_victor(&data->player.vdir, 2);
		rotate_victor(&data->player.plane, 2);
	}
	if (x < data->player.mouse_x && \
	data->player.mouse_x < data->map.width * data->map.ppc && \
	data->player.mouse_x > 0)
	{
		rotate_victor(&data->player.vdir, -2);
		rotate_victor(&data->player.plane, -2);
	}
	data->player.mouse_x = x;
	data->player.mouse_y = y;
	if (data->sprites[PISTOL_BANG]->instances[0].enabled == true)
		data->sprites[PISTOL_BANG]->instances[0].enabled = false;
	if (data->sprites[PISTOL]->instances[0].enabled == false)
		data->sprites[PISTOL]->instances[0].enabled = true;
}
