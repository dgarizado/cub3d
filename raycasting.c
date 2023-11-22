/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:33:42 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/22 12:36:18 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	detras_de_steven_bonus( t_data *data, int n, float angle)//0delante 1 atras
{
	 if(data->cast.bonus.flag_bonus[n] == 'x' && data->cast.bonus.cell_step_bonus[n] == -1 && (data->cast.bonus.current_cell_bonus[n] ) < (int)data->steven_x )//X
		return 1;
	else if(data->cast.bonus.flag_bonus[n] == 'x' && data->cast.bonus.cell_step_bonus[n] == 1 && (data->cast.bonus.current_cell_bonus[n] ) > (int)data->steven_x)
			return 1;
	else if(data->cast.bonus.flag_bonus[n] == 'y' && data->cast.bonus.cell_step_bonus[n] == -1 && (data->cast.bonus.current_cell_bonus[n] ) < (int)data->steven_y )//   Y
		return 1;
	else if(data->cast.bonus.flag_bonus[n] == 'y' && data->cast.bonus.cell_step_bonus[n] == 1 && (data->cast.bonus.current_cell_bonus[n] ) > (int)data->steven_y)
		return 1;
	return 0;
	/*---------------------------PUNTO DE REFERENCIA RESPECTO A PUNTO DE INTERES------------------------------------------*/
	// //punto referencia
	// double x1 = data->steven_x;
    // double y1 = data->steven_y;

    // // Punto de interés
    // double x2 = data->px + (data->cast.bonus.distance[n] * cos((ft_degre_to_radian(angle))));
    // double y2 = data->py + (data->cast.bonus.distance[n] * sin((ft_degre_to_radian(angle))));

    // // Ángulo en radianes con respecto al eje X
    // double theta = M_PI / (data->angle_steven + 90);
	// double theta2 = M_PI / (data->angle_steven + 270);

    // // Coordenadas relativas al punto de referencia
    // double relX = x2 - x1;
    // double relY = y2 - y1;

    // // Ángulo polar
    // double phi = atan2(relY, relX);

    // // Comparación de ángulos
    // if (phi < theta  || phi < theta2) {
	// 	return 1;
    //     //printf("El punto de interés está detrás del punto de referencia.\n");
    // } else {
	// 	return 0;
    //     //printf("El punto de interés está delante del punto de referencia.\n");
    // }

   

/*------------------------------------------------------------------------------------------------------------*/
	/*------------------------------------------A OSTIAS CON PITAGORAS----------------------------------------*/
	
	// int lado_1;
	// int lado_2;
	// int lado_3;
	// int A;
	// int B;
	// int C;
	
	// int x1 = data->px;
	// int y1 = data->py;
	// //colision
	// int x2 = data->px + (data->cast.bonus.distance[n] * cos((ft_degre_to_radian(angle))));
	// int y2 = data->py + (data->cast.bonus.distance[n] * sin((ft_degre_to_radian(angle))));
	// //steven
	// int x3 = data->steven_x;
	// int y3 = data->steven_y;
	// 	lado_1 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	// 	lado_2 = sqrt(pow(x3 - y2, 2) + pow(y3 - x2, 2));
	// 	lado_3 = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
	// //ASIGNAR CATETOS E HIPOTENUSA
	// if (lado_1 > lado_2 && lado_1 > lado_3)
	// {
	// 	C = lado_1;
	// 	A = lado_2;
	// 	B = lado_3; 
	// }
	// else if (lado_2 > lado_1 && lado_2 > lado_3)
	// {
	// 	C = lado_2;
	// 	A = lado_1;
	// 	B = lado_3; 
	// }
	// else if (lado_3 > lado_1 && lado_3 && lado_2)
	// {
	// 	C = lado_3;
	// 	A = lado_1;
	// 	B = lado_2; 
	// }
	// //torema de los catetos
	// float cosA = -((pow(A,2) - pow(B, 2) - pow(C, 2)) / (2* (B*C)));
	// cosA = acos(cosA);
    // cosA = cosA * (180.0 / M_PI);
	// float cosB = -((pow(B,2) - pow(A, 2) - pow(C, 2)) / (2* (A*C)));
	// cosB = acos(cosB);
    // cosB = cosB * (180.0 / M_PI);
	// float cosC = -((pow(C,2) - pow(A, 2) - pow(B, 2)) / (2* (A*B)));
    // cosC = acos(cosC);
    // cosC = cosC * (180.0 / M_PI);

	// if (cosA > 90.0 || cosB > 90.0 || cosC > 90.0)
	// 	return 1;
	// return 0;
	// /*------------------------------------------------------------------------------------------------------*/
}

void draw_colision(int rayCount, float angle, int n, t_data *data)
{
	int colum_texture;
	int wallheight;
	float ray_end_x;
	float ray_end_y;
	
	ray_end_x = data->px + (data->cast.bonus.distance[n] * cos((ft_degre_to_radian(angle))));
	ray_end_y = data->py + (data->cast.bonus.distance[n] * sin((ft_degre_to_radian(angle))));
	if(fabs(ray_end_x - round(ray_end_x)) > fabs(ray_end_y - round(ray_end_y)))//horizontal
		colum_texture = (int)(ray_end_x * 1000) % 1000;
	else	//vertical
	colum_texture = (int)(ray_end_y * 1000) % 1000;
	data->cast.bonus.distance[n] = fix_fish_eye(data->cast.bonus.distance[n], angle,  data->angle);
	//wallheight = floor(HEIGHT/2)  /  data->cast.bonus.distance[n];
	wallheight = floor(data->mlx->height/2)  /  data->cast.bonus.distance[n];
	if (last_colision_arr(data->cast.bonus.type_wall_bonus) == n)//ONLY DRAW IN LAST COLISIONS MEANS WALL OPTIMITATION
	{
		drawLine(rayCount, 0, rayCount, (HEIGHT/2) - wallheight , 0x00FFFF1A, data->img[GAME],data);
		drawLine(rayCount, (HEIGHT/2)+ wallheight, rayCount, HEIGHT, 0x00FF001A, data->img[GAME],data);
	}
	drawLineTexture_bonus(rayCount, (data->mlx->height/2) - wallheight, (data->mlx->height/2) + wallheight, colum_texture, data, n);
}

void draw_colisions(int rayCount, float angle, int flag, t_data *data)// flag 0 delante 1 atras
{
	int n;
	
	n = last_colision_arr(data->cast.bonus.type_wall_bonus); //get last colision
	while(n >= 0)
	{
		if(detras_de_steven_bonus(data, n, angle) == flag)
			draw_colision(rayCount, angle, n, data);
		n--;
	}
}

void raycast_game(mlx_image_t *game, t_data *data)
{
	float increment_angle = 60.0f/WIDTH;//HARCODED***********************************
	float angle;
	
	angle = data->angle - 30;
	for(int rayCount = 0; rayCount < WIDTH; rayCount++) 
	{
		ft_memset((&data->cast.bonus), 0, sizeof(t_bonus));//borrar primero array
		rays(data->img[GAME], data, angle);//fill array colisions
		draw_colisions(rayCount, angle, 1, data);
	 	angle+= increment_angle;
	}
	draw_steven_sprite(data);
	angle = data->angle - 30;
	for(int rayCount = 0; rayCount < WIDTH; rayCount++) 
	{
	 	ft_memset((&data->cast.bonus), 0, sizeof(t_bonus));//borrar primero array
		rays(data->img[GAME], data, angle);//fill array colisions
		draw_colisions(rayCount, angle, 0, data);
	 	angle+= increment_angle;
	}
}
