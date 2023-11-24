/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:51:54 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/24 17:43:06 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_key(double *temp, t_data *d)
{
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
	{
		temp[0] = d->px + (cos(ft_degre_to_radian(d->angle)) * DIST_FACTOR);
		temp[1] = d->py + (sin(ft_degre_to_radian(d->angle)) * DIST_FACTOR);
	}
	else if (mlx_is_key_down(d->mlx, MLX_KEY_S))
	{
		temp[0] = d->px - (cos(ft_degre_to_radian(d->angle)) * DIST_FACTOR);
		temp[1] = d->py - (sin(ft_degre_to_radian(d->angle)) * DIST_FACTOR);
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
	{
		temp[0] = d->px + (cos(ft_degre_to_radian(d->angle - 90)) \
		* DIST_FACTOR);
		temp[1] = d->py + (sin(ft_degre_to_radian(d->angle - 90)) \
		* DIST_FACTOR);
	}
	else if (mlx_is_key_down(d->mlx, MLX_KEY_D))
	{
		temp[0] = d->px + (cos(ft_degre_to_radian(d->angle + 90)) \
		* DIST_FACTOR);
		temp[1] = d->py + (sin(ft_degre_to_radian(d->angle + 90)) \
		* DIST_FACTOR);
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

void	ft_move_steven(double *temp, double *ptr_x, double *ptr_y, t_data *d)
{
	float	dx;
	float	dy;
	float	angle_steven;

	dx = d->px - d->steven_x;
	dy = d->py - d->steven_y;
	angle_steven = radianes_a_grados(atan2(dy, dx));
	d->angle_steven = angle_steven;
	dx = cos(ft_degre_to_radian(angle_steven));
	dy = sin(ft_degre_to_radian(angle_steven));
	temp[0] = d->steven_x + dx * DIST_FACTOR_STEVEN;
	temp[1] = d->steven_y + dy * DIST_FACTOR_STEVEN;
}

int	ft_check_game_over(t_data *d)
{
	if (sqrt(pow((d->py - d->steven_y), 2) + pow(d->px - d->steven_x, 2)) < 1)
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
