/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:51:54 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/24 14:17:15 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_wall(double x, double y, t_data *data)
{
	double	radio;
	int		angulo;
	double	radianes;
	int		circle_x;
	int		circle_y;

	angulo = 0;
	radio = 200.0f / 1000.0f;
	while (angulo <= 360)
	{
		radianes = angulo * (M_PI / 180.0);
		circle_x = x + (radio * cos(radianes));
		circle_y = y + (radio * sin(radianes));
		if (data->map.map_aclean[circle_y][circle_x] == '1' || data->map.map_aclean[circle_y][circle_x] == '9')
			return (1);
		angulo = angulo + 20;
	}
	return (0);
}

void	ft_check_move(double *temp, double *ptr_x, double *ptr_y, t_data *data)
{
	if (ft_wall(temp[0], temp[1], data) == 0)
	{
		*ptr_x = temp[0];
		*ptr_y = temp[1];
	}
	else if (ft_wall(temp[0], *ptr_y, data) == 0)
		*ptr_x = temp[0];
	else if (ft_wall(*ptr_x, temp[1], data) == 0)
		*ptr_y = temp[1];
}

void	check_key(double *temp, t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		temp[0] = data->px + (cos(ft_degre_to_radian(data->angle)) * DIST_FACTOR);
		temp[1] = data->py + (sin(ft_degre_to_radian(data->angle)) * DIST_FACTOR);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		temp[0] = data->px - (cos(ft_degre_to_radian(data->angle)) * DIST_FACTOR);
		temp[1] = data->py - (sin(ft_degre_to_radian(data->angle)) * DIST_FACTOR);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		temp[0] = data->px + (cos(ft_degre_to_radian(data->angle - 90)) * DIST_FACTOR);
		temp[1] = data->py + (sin(ft_degre_to_radian(data->angle - 90)) * DIST_FACTOR);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		temp[0] = data->px + (cos(ft_degre_to_radian(data->angle + 90)) * DIST_FACTOR);
		temp[1] = data->py + (sin(ft_degre_to_radian(data->angle + 90)) * DIST_FACTOR);
	}
}

void	ft_check_key(double *temp, t_data *data)
{
	check_key(temp, data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->angle -= 5;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->angle += 5;
	if (data->angle > 360.0)
		data->angle = fmod(data->angle, 360);
	else if (data->angle < 0)
		data->angle += 360;
}

void	ft_move_steven(double *temp, double *ptr_x, double *ptr_y, t_data *data)
{
	float	dx;
	float	dy;
	float	angle_steven;

	dx = data->px - data->steven_x;
	dy = data->py - data->steven_y;
	angle_steven = radianes_a_grados(atan2(dy, dx));
	data->angle_steven = angle_steven;
	dx = cos(ft_degre_to_radian(angle_steven));
	dy = sin(ft_degre_to_radian(angle_steven));
	temp[0] = data->steven_x + dx * DIST_FACTOR_STEVEN;
	temp[1] = data->steven_y + dy * DIST_FACTOR_STEVEN;
}

void	ft_check_door(t_data *data)
{
	float	x;
	float	y;

	if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
	{
		x = cos(ft_degre_to_radian(data->angle)) * 0.5;
		y = sin(ft_degre_to_radian(data->angle)) * 0.5;
		if (data->map.map_aclean[(int)(data->py + y)][(int)(data->px + x)] == '9')
			data->map.map_aclean[(int)(data->py + y)][(int)(data->px + x)] = 'B';
	}
}

int	ft_check_game_over(t_data *data)
{
	if (sqrt(pow((data->py - data->steven_y), 2) + pow(data->px - data->steven_x, 2)) < 1)
		return (1);
	return (0);
}

void	ft_move_players(t_data *data)
{
	double	temp[2];

	temp[0] = data->px;
	temp[1] = data->py;
	ft_check_key(temp, data);
	if (ft_check_game_over(data) == 0)
	{
		ft_check_move(temp, &data->px, &data->py, data);
		ft_move_steven(temp, &data->steven_x, &data->steven_y, data);
		ft_check_move(temp, &data->steven_x, &data->steven_y, data);
	}
}
