/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_minimap_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:57:25 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/27 20:26:47 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	paint_collision_aux(t_data *data, float x, float y)
{
	if (data->cast.ray_x_start * data->scale_x + x > 0 && data->cast.ray_x_start
		* data->scale_x + x < data->mlx->width * 0.3 \
		&& data->cast.ray_y_start * data->scale_y
		+ y > 0 && data->cast.ray_y_start * data->scale_y \
		+ y < (int)data->mlx->height * 0.3)
		mlx_put_pixel(data->img[MINIMAP_GAME], data->cast.ray_x_start
			* data->scale_x + x, data->cast.ray_y_start * data->scale_y + y,
			0xFFFF00FF);
}

void	paint_colision_map(t_data *data)
{
	int		radio;
	int		angulo;
	float	x;
	float	y;
	float	radianes;

	radio = 2;
	angulo = 0;
	while (angulo <= 360)
	{
		x = data->cast.ray_x_direction * \
		(data->cast.ray_length * data->scale_x);
		y = data->cast.ray_y_direction * \
		(data->cast.ray_length * data->scale_y);
		radianes = angulo * (M_PI / 180.0);
		x = x + (radio * cos(radianes));
		y = y + (radio * sin(radianes));
		paint_collision_aux(data, x, y);
		angulo += 10;
	}
}

void	draw_raycast_map(t_data *data)
{
	float	angle;
	float	ang;

	ang = 0;
	angle = data->angle - 30;
	while (ang <= 60)
	{
		rays(data, angle + ang);
		paint_colision_map(data);
		ang++;
	}
}
