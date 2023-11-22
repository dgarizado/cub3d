/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:51:54 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/22 11:19:12 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_wall(double x, double y, t_data *data)
{
	double radio = 12; radio /=1000;//radio/=data->size;//harcoded ******************
	for (int angulo = 0; angulo <= 360; angulo= angulo + 20) {
        double radianes = angulo * (M_PI / 180.0);
        int circle_x = x + (radio * cos(radianes));
        int circle_y = y + (radio * sin(radianes));
		if(data->map.map_aclean[circle_y][circle_x] == '1' || data->map.map_aclean[circle_y][circle_x] == '9')
			return 1;
	}
	return 0;
}

void ft_check_move(double tempx, double tempy, double *ptr_x, double *ptr_y, t_data *data)
{
	if(ft_wall(tempx, tempy, data) == 0)
	{
		*ptr_x = tempx;
		*ptr_y = tempy;
	}
	else if(ft_wall(tempx, *ptr_y, data) == 0)
		*ptr_x = tempx;
	else if(ft_wall(*ptr_x, tempy, data) == 0)
		*ptr_y = tempy;
}

void ft_check_key(double *tempx, double *tempy, t_data *data)
{
	if (mlx_is_key_down(data->mlx, 256))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		*tempx = data->px + (cos(ft_degre_to_radian(data->angle)) * DIST_FACTOR);
		*tempy = data->py + (sin(ft_degre_to_radian(data->angle)) * DIST_FACTOR);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		*tempx = data->px - (cos(ft_degre_to_radian(data->angle)) * DIST_FACTOR);
		*tempy = data->py - (sin(ft_degre_to_radian(data->angle)) * DIST_FACTOR);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		*tempx = data->px + (cos(ft_degre_to_radian(data->angle - 90)) * DIST_FACTOR);
		*tempy = data->py + (sin(ft_degre_to_radian(data->angle - 90)) * DIST_FACTOR);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		*tempx = data->px + (cos(ft_degre_to_radian(data->angle + 90)) * DIST_FACTOR);
		*tempy = data->py + (sin(ft_degre_to_radian(data->angle + 90)) * DIST_FACTOR);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->angle -=5;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->angle +=5;
	//NORMALIZAR ANGULOOOO PLAYER
	if (data->angle > 360.0)
		data->angle = fmod(data->angle, 360);
	else if (data->angle < 0)
		data->angle +=360;
}

void ft_move_steven(double *tempx, double *tempy, double *ptr_x, double *ptr_y, t_data *data)
{
	//player px,py  steven steven_x, steven_y
	//
	float dx = data->px - data->steven_x ;
	float dy = data->py - data->steven_y;
	float angle_steven;

	angle_steven = radianes_a_grados(atan2(dy, dx));
	data->angle_steven = angle_steven;
	dx = cos(ft_degre_to_radian(angle_steven));//longitud rayo direccion *30para ampliarlo
	dy = sin(ft_degre_to_radian(angle_steven));
	*tempx = data->steven_x + dx * DIST_FACTOR_STEVEN;
	*tempy = data->steven_y + dy * DIST_FACTOR_STEVEN;
	drawLine((data->steven_x *SCALE_X) + dx*SCALE_X, (data->steven_y *SCALE_Y) + dy*SCALE_Y, (data->steven_x *SCALE_X), (data->steven_y *SCALE_Y), 0x00FF40FF, data->img[MINIMAP_GAME], data);
	//harcoded a 100 es escala!!!
}

void ft_check_door(t_data *data)
{
	float x;
	float y;

	if(mlx_is_key_down(data->mlx, MLX_KEY_Q))
	{
		x = cos(ft_degre_to_radian(data->angle)) * 0.1;		//lHARCODED  LONGITUD RAYO ROJO MINIMAP
		y = sin(ft_degre_to_radian(data->angle)) * 0.1;		//HARCODED  LONGITUD RAYO ROJO MINIMAP

		if(data->map.map_aclean[(int)(data->py + y)][(int)(data->px + x)] == '9')
			data->map.map_aclean[(int)(data->py + y)][(int)(data->px + x)] = '8';
	}
}

int ft_check_game_over(t_data *data)
{
	if (sqrt(pow((data->py - data->steven_y),2) + pow(data->px - data->steven_x, 2)) < 1)//distancia entre steven y player < 1 GAME OVER!
		return 1;
	return (0);
}

void ft_move_players(t_data *data)
{
	double tempx = data->px;
	double tempy = data->py;

	usleep(500);
	ft_check_key(&tempx, &tempy, data);
	if (ft_check_game_over(data) == 0)
	{
		ft_check_move(tempx, tempy, &data->px, &data->py, data);
		ft_move_steven(&tempx, &tempy, &data->steven_x, &data->steven_y, data);
		ft_check_move(tempx, tempy, &data->steven_x, &data->steven_y, data);
	}
}