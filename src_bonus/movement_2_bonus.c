/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:39:44 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/26 20:31:59 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"

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

		x = cos(ft_degre_to_radian(d->angle)) * 1.1;
		y = sin(ft_degre_to_radian(d->angle)) * 1.1;
		if (d->map.map_aclean[(int)(d->py + y)][(int)(d->px + x)] == '9')
			d->map.map_aclean[(int)(d->py + y)][(int)(d->px + x)] = 'B';
		else if (d->map.map_aclean[(int)(d->py + y)][(int)(d->px + x)] == 'D')
			d->map.map_aclean[(int)(d->py + y)][(int)(d->px + x)] = 'O';
		else if (d->map.map_aclean[(int)(d->py + y)][(int)(d->px + x)] == 'O')
			d->map.map_aclean[(int)(d->py + y)][(int)(d->px + x)] = 'D';
}

void	mouse(t_data *data)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (x > data->mouse_x && data->mouse_x > 0 \
	&& data->mouse_x < data->mlx->width)
	{
		data->angle += 2;
	}
	if (x < data->mouse_x && \
	data->mouse_x < data->mlx->width && \
	data->mouse_x > 0)
	{
		data->angle -= 2;
	}
	data->mouse_x = x;
	data->mouse_y = y;
	if (data->sprites[PISTOL_BANG]->instances[0].enabled == true)
		data->sprites[PISTOL_BANG]->instances[0].enabled = false;
	if (data->sprites[PISTOL]->instances[0].enabled == false)
		data->sprites[PISTOL]->instances[0].enabled = true;
}

