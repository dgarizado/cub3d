/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:57:25 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/24 17:57:25 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void paint_colision_map(t_data *data)
{
	int radio;
	int angulo;
	
	radio = 2;
	angulo = 0;

		while (angulo <= 360)
		{
			int x = data->cast.ray_x_direction * (data->cast.ray_length * SCALE_X);
		int y = data->cast.ray_y_direction * (data->cast.ray_length * SCALE_Y);
		float radianes = angulo * (M_PI / 180.0);
		float xx =radio * cos(radianes);
		float yy = radio * sin(radianes);
		if (data->cast.ray_x_start * SCALE_X + x + xx > 0 && data->cast.ray_x_start * SCALE_X + x + xx < WIDTH_MAP_GAME && data->cast.ray_y_start *SCALE_Y + y + yy > 0 && data->cast.ray_y_start *SCALE_Y + y + yy < HEIGHT_MAP_GAME)
			mlx_put_pixel(data->img[MINIMAP_GAME], data->cast.ray_x_start * SCALE_X + x + xx ,data->cast.ray_y_start *SCALE_Y + y + yy , 0xFFFF00FF);
			angulo+=10;
		}

	
	// for (int ang = 0; ang <= 3; ang++)
	// {
	// 	for (int angulo = 0; angulo <= 360; angulo+=10) {

	// 	int x = data->cast.ray_x_direction * (data->cast.ray_length * SCALE_X);
	// 	int y = data->cast.ray_y_direction * (data->cast.ray_length * SCALE_Y);
	// 	float radianes = angulo * (M_PI / 180.0);
	// 	float xx =radio * cos(radianes);
	// 	float yy = radio * sin(radianes);
	// 	if (data->cast.ray_x_start * SCALE_X + x + xx > 0 && data->cast.ray_x_start * SCALE_X + x + xx < WIDTH_MAP_GAME && data->cast.ray_y_start *SCALE_Y + y + yy > 0 && data->cast.ray_y_start *SCALE_Y + y + yy < HEIGHT_MAP_GAME)
	// 		mlx_put_pixel(data->img[MINIMAP_GAME], data->cast.ray_x_start * SCALE_X + x + xx ,data->cast.ray_y_start *SCALE_Y + y + yy , 0xFFFF00FF);
	// }
	// radio = radio -1;
	// }
}

void	draw_raycast_map(mlx_image_t *map, t_data *data)
{
	float	angle;
	float	ang;
	
	ang = 0;
	angle = data->angle - 30;
	while (ang <= 60)
	{
		rays(map, data, angle + ang);
		paint_colision_map(data);
		ang++;
	}
}
