/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:19:52 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/20 15:50:59 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double radianes_a_grados(double radianes) {
    double grados = radianes * (180.0 / M_PI);

    grados = fmod(grados, 360.0);
    if (grados < 0) {
        grados += 360.0;
    }
    return grados;
}

double ft_degre_to_radian(double degre)
{
	double radian;

	radian = degre * (M_PI / 180);
	return (radian);
}

void drawLine(double x1, double y1, double x2, double y2, int color, mlx_image_t *ptr, t_data *data)
{
	double dx = x2 - x1;
	double dy =  y2 -y1;
	double steps;

	if ((abs)((int)dx) >= (abs)((int)dy))
		steps = (fabs)(dx);
	else
		steps = (fabs)(dy);

	dx = dx / steps;
	dy = dy / steps;
	while ((int)fabs(x2 - x1) || (int)fabs(y2 - y1))
	{
		if(x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
		//if(x1 >= 0 && x1 <= WIDTH_MAP_GAME && y1 >= 0 && y1 <= HEIGHT_MAP_GAME)
			mlx_put_pixel(ptr, (int)x1, (int)y1, color);
		x1 += dx;
		y1 += dy;
	}
}

void normalize_angle(double *angulo_me, double *angle_steven_from_me)
{
	if (*angle_steven_from_me > 360.0)
		*angle_steven_from_me = fmod(*angle_steven_from_me, 360);
	else if ( *angle_steven_from_me < 0)
		*angle_steven_from_me +=360;


	if ( *angulo_me > 360.0)
		*angulo_me = fmod(*angulo_me, 360);
	else if ( *angulo_me < 0)
		*angulo_me +=360;
}

int last_colision_arr(int *arr)
{
	int n;

	n = 0;
	while(arr[n + 1] != 0)
		n++;
	return (n);
}

int	ft_changed_resolution(t_data *data)
{
	if ((int)(data->mlx->width) != (int)(data->screen_width) || (int)(data->mlx->height) != (int)(data->screen_heigth))
	{
		data->screen_width = data->mlx->width;
		data->screen_heigth = data->mlx->height;
		return (1);
	}
	return (0);
}