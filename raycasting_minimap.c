/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:57:25 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/24 18:40:20 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		x = data->cast.ray_x_direction * (data->cast.ray_length * SCALE_X);
		y = data->cast.ray_y_direction * (data->cast.ray_length * SCALE_Y);
		radianes = angulo * (M_PI / 180.0);
		x = x + (radio * cos(radianes));
		y = y + (radio * sin(radianes));
		if (data->cast.ray_x_start * SCALE_X + x > 0 && data->cast.ray_x_start \
		* SCALE_X + x < WIDTH_MAP_GAME && data->cast.ray_y_start * SCALE_Y + \
		y > 0 && data->cast.ray_y_start * SCALE_Y + y < HEIGHT_MAP_GAME)
			mlx_put_pixel(data->img[MINIMAP_GAME], data->cast.ray_x_start * \
			SCALE_X + x, data->cast.ray_y_start * SCALE_Y + y, 0xFFFF00FF);
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
