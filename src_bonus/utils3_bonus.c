/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:19:52 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/27 19:10:30 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		if (p->x1 >= 0 && p->x1 <= data->mlx->width && \
		p->y1 >= 0 && p->y1 <= data->mlx->height)
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
