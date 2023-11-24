/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:39:44 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/24 17:43:15 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_wall(double x, double y, t_data *d)
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
		if (d->map.map_aclean[circle_y][circle_x] == '1' || \
		d->map.map_aclean[circle_y][circle_x] == '9' || \
		d->map.map_aclean[circle_y][circle_x] == 'D')
			return (1);
		angulo = angulo + 20;
	}
	return (0);
}

void	ft_check_move(double *temp, double *ptr_x, double *ptr_y, t_data *d)
{
	if (ft_wall(temp[0], temp[1], d) == 0)
	{
		*ptr_x = temp[0];
		*ptr_y = temp[1];
	}
	else if (ft_wall(temp[0], *ptr_y, d) == 0)
		*ptr_x = temp[0];
	else if (ft_wall(*ptr_x, temp[1], d) == 0)
		*ptr_y = temp[1];
}

void	ft_check_interaction(t_data *d)
{
	float	x;
	float	y;

	if (mlx_is_key_down(d->mlx, MLX_KEY_Q))
	{
		x = cos(ft_degre_to_radian(d->angle)) * 0.5;
		y = sin(ft_degre_to_radian(d->angle)) * 0.5;
		if (d->map.map_aclean[(int)(d->py + y)][(int)(d->px + x)] == '9')
			d->map.map_aclean[(int)(d->py + y)][(int)(d->px + x)] = 'B';
		else if (d->map.map_aclean[(int)(d->py + y)][(int)(d->px + x)] == 'D')
			d->map.map_aclean[(int)(d->py + y)][(int)(d->px + x)] = 'O';
	}
}
