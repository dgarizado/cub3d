/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:56:18 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/22 11:19:23 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void paint_square(int column, int row, int color, t_data *data)
{
	int y;

	y = 0;
	//while(y < data->size)
	while(y < HEIGHT_MAP_GAME/data->map.height &&  row * SCALE_Y + y < HEIGHT_MAP_GAME)
	{
		if ((column * SCALE_X) + SCALE_X <= WIDTH_MAP_GAME)
			drawLine(column * SCALE_X , row * SCALE_Y + y, (column * SCALE_X) + SCALE_X, row *SCALE_Y + y, color, data->img[MINIMAP_GAME], data);
		y++;
	}
}

void draw_squares(t_data *data)
{
	int x;
	int y;
	
	y= 0;
	while (y < data->map.height)//HARCODED ANCHO MAP
	{
		x = 0;
		while (x < data->map.width)//AHARCODED LARGO MAP
		{
			if (data->map.map_aclean[y][x] == '1' || data->map.map_aclean[y][x] == '9')		
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
		if (x > 0 && x < WIDTH_MAP_GAME && y > 0 && y < HEIGHT_MAP_GAME)
        	mlx_put_pixel(data->img[MINIMAP_GAME], x, y, 0xFFFFFFFF);
    }
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
			if (x > 0 && x < WIDTH_MAP_GAME && y > 0 && y < HEIGHT_MAP_GAME)
				mlx_put_pixel(data->img[MINIMAP_GAME], x, y, 0xFF0000FF);
		}
		radio--;
	}
}

void ft_draw_minimap(t_data *data)
{
	draw_squares(data);
	draw_player(data, 5);//HARCODED A RADIO 10
	draw_steven(data, 5);//HARCODED A RADIO 10
	
	draw_raycast_map(data->img[MINIMAP_GAME], data);
}