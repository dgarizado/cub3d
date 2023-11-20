/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:57:25 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/20 14:25:23 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float fix_fish_eye(float distance, float angle, float angle_player)
{
	distance = distance * cos(ft_degre_to_radian(angle - angle_player));
	return (distance);
}

void paint_colision_map(float distance, t_data *data)
{
	int radio = 3;
	for (int ang = 0; ang <= 3; ang++)
	{
		for (int angulo = 0; angulo <= 360; angulo+=10) { //dibujar circulo con radio 10????
		//int x = data->cast.ray_x_direction * (data->cast.ray_length * data->size);//longitud rayo direccion *30para ampliarlo
		//int y = data->cast.ray_y_direction * (data->cast.ray_length * data->size);
		int x = data->cast.ray_x_direction * (data->cast.ray_length * SCALE_X);//longitud rayo direccion *30para ampliarlo
		int y = data->cast.ray_y_direction * (data->cast.ray_length * SCALE_Y);
		float radianes = angulo * (M_PI / 180.0);
		float xx =radio * cos(radianes);
		float yy = radio * sin(radianes);
		mlx_put_pixel(data->map, data->cast.ray_x_start * SCALE_X + x + xx ,data->cast.ray_y_start *SCALE_Y + y + yy , 0xFFFF00FF);
	}
	radio = radio -1;
	}
}

void draw_raycast_map(mlx_image_t *map, t_data *data)
{
	float distance;
	float angle = data->angle - 30;
	for (float angulo = 0; angulo <= 60; angulo+= 1) { //dibujar circulo con radio 10????
		distance = rays(map, data, angle + angulo);
		paint_colision_map(distance, data);
	}
}
