/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:56:18 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/20 15:24:14 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void paint_square(int column, int row, int color, t_data *data)
{
	int y;

	y = 0;
	//while(y < data->size)
	while(y < HEIGHT_MAP_GAME/data->anchoMapa)
	{
		drawLine(column * SCALE_X , row * SCALE_Y + y, (column * SCALE_X) + SCALE_X, row *SCALE_Y + y, color, data->map, data);
		y++;
	}
}

void draw_squares(t_data *data)
{
	int x;
	int y;
	
	y= 0;
	while (y < data->anchoMapa)//HARCODED ANCHO MAP
	{
		x = 0;
		while (x < data->largoMapa)//AHARCODED LARGO MAP
		{
			if (data->arr[(y * data->largoMapa) + x] == 1 || data->arr[(y * data->largoMapa) + x] == 9)			//harcdodeed!!!! WALL 1 BONUS WALL 9
				paint_square(x, y, 0xFFFFFFFF, data);
			x++;
		}
		y++;
	}
}

void draw_player(t_data *data, int radio)
{
    double radianes;
	double x;
	double y;
	
	for (int angulo = 0; angulo <= 360; angulo+=5) { //dibujar circulo con radio 10????
		radianes = angulo * (M_PI / 180.0);
       // x = (data->px *data->size)+ (radio * cos(radianes));
       // y = (data->py *data->size) + (radio * sin(radianes));
		x = (data->px * SCALE_X)+ (radio * cos(radianes));
       	y = (data->py *SCALE_Y) + (radio * sin(radianes));
        mlx_put_pixel(data->map, x, y, 0xFFFFFFFF);
    }
	x = cos(ft_degre_to_radian(data->angle)) * (SCALE_X);//longitud rayo direccion *30para ampliarlo HARCODED
	y = sin(ft_degre_to_radian(data->angle)) * (SCALE_Y);
	drawLine((data->px * SCALE_X), (data->py *SCALE_Y), (data->px *SCALE_X) + x, (data->py *SCALE_Y) + y, 0xFF1111FF, data->map, data);
}

void draw_steven(t_data *data, int radio)
{
    double radianes;
	double x;
	double y;
	for (int n = 0; n <= 10; n++)
	{
		for (int angulo = 0; angulo <= 360; angulo+=36) { //dibujar circulo con radio 10????
			radianes = angulo * (M_PI / 180.0);
			x = (data->steven_x * SCALE_X)+ (radio * cos(radianes));
			y = (data->steven_y * SCALE_Y) + (radio * sin(radianes));
			mlx_put_pixel(data->map, x, y, 0xFF0000FF);
		}
		radio--;
	}
}

void ft_draw_minimap(t_data *data)
{
	draw_squares(data);
	draw_player(data, 5);//HARCODED A RADIO 10
	draw_steven(data, 5);//HARCODED A RADIO 10
	draw_raycast_map(data->map, data);
}