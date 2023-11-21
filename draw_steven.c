/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_steven.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:04:01 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/20 16:15:46 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int casi_iguales(double izquierda, double derecha)
{
	if (fabs(izquierda - derecha) <= 0.1)
		return (1);
	return 0;
}

void ft_draw_steven(float wallheight, float column, t_data *data)
{
	column = column - wallheight/2;
	
	int column_texture = 0; 
	float incremente_texture_column = data->wall_img->width/wallheight;
	int n = 0.0;

	data->cast.type_wall = 7;
	while(column_texture < data->zombie->width)
	{
		column_texture = incremente_texture_column * n;
		//drawLineTexture_bonus(column, ((HEIGHT) / 2) , ((HEIGHT) / 2)+ (wallheight), (int)column_texture, data, -1);
		drawLineTexture_bonus(column, ((data->mlx->height) / 2) , ((data->mlx->height) / 2)+ (wallheight), (int)column_texture, data, -1);
		n++;
		column++;
		//printf("COLUMNA==%f  \n", column);
		//printf("COLUMNA TEXTURE==%d  \n", column_texture);
	}
}

void get_distance_steven(double column, t_data *data, double angle_me)
{
	float dx = data->px - data->steven_x ;
	float dy = data->py - data->steven_y;

	float distance;
	float wallheight;

	distance = sqrt(pow(dy,2) + pow(dx, 2));
	distance = fix_fish_eye(distance, angle_me,  data->angle);
 //	wallheight = floor((HEIGHT)/2) / distance;
		wallheight = floor((data->mlx->height) / 2) / distance;
	ft_draw_steven(wallheight, column, data);
}


void draw_steven_sprite(t_data *data)
{
	double angle_steven_from_me = data->angle_steven -180;
	double angulo_me =data->angle -30;
	
	normalize_angle(&angulo_me, &angle_steven_from_me);
	//printf("---ANGLE  STEVEN FROM ME==%f  STEVEN= %f\n", angle_steven_from_me, data->angle_steven);
	//printf("ANGLE  ME==%f  TARjet= %f\n", angulo_me, angle_steven_from_me);
	float increment_angle = 60.0f/WIDTH;//HARCODED A 1000 ANCHO PANTALLA
	for(int column= 0; column < WIDTH; column++)
	{
		if (casi_iguales(angulo_me, angle_steven_from_me) == 1)
		{ 
		//	printf("ANGLE  STEVEN FROM ME==%f  STEVEN= %f\n", angle_steven_from_me, data->angle_steven);
			//printf("DRAW!\n");
			//printf("ANGLE  ME==%f  TARjet= %f\n", angulo_me, angle_steven_from_me);
			get_distance_steven(column, data, angulo_me);
			break;
		}
		angulo_me+=increment_angle;// antes de normalizar
		normalize_angle(&angulo_me, &angle_steven_from_me);
	}
}