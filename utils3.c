/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:19:52 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/24 12:50:55 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	radianes_a_grados(double radianes)
{
	double	grados;

	grados = radianes * (180.0 / M_PI);
	grados = fmod(grados, 360.0);
	if (grados < 0)
		grados += 360.0;
	return (grados);
}

double	ft_degre_to_radian(double degre)
{
	double	radian;

	radian = degre * (M_PI / 180);
	return (radian);
}

void	drawline(t_coord *p, int color, mlx_image_t *ptr, t_data *data)
{
	double	dx;
	double	dy;
	double	steps;

	dx = p->x2 - p->x1;
	dy = p->y2 - p->y2;
	if (fabs(dx) >= fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	dx = dx / steps;
	dy = dy / steps;
	while (p->x2 - p->x1 || p->y2 - p->y1)
	{
		if (p->x1 >= 0 && p->x1 <= WIDTH && p->y1 >= 0 && p->y1 <= HEIGHT)
			mlx_put_pixel(ptr, (int)p->x1, (int)p->y1, color);
		p->x1 += dx;
		p->y1 += dy;
	}
}

void	normalize_angle(double *angulo_me, double *angle_steven_from_me)
{
	if (*angle_steven_from_me > 360.0)
		*angle_steven_from_me = fmod(*angle_steven_from_me, 360);
	else if (*angle_steven_from_me < 0)
		*angle_steven_from_me += 360;
	if (*angulo_me > 360.0)
		*angulo_me = fmod(*angulo_me, 360);
	else if (*angulo_me < 0)
		*angulo_me += 360;
}

int	last_colision_arr(int *arr)
{
	int	n;

	n = 0;
	while (arr[n + 1] != 0)
		n++;
	return (n);
}

int	ft_changed_resolution(t_data *data)
{
	if ((int)(WIDTH) != (int)(data->screen_width) || (int)(HEIGHT) != (int)(data->screen_heigth))
	{
		data->screen_width = WIDTH;
		data->screen_heigth = HEIGHT;
		return (1);
	}
	return (0);
}
