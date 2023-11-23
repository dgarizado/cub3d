/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 00:47:57 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/23 20:36:29 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
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
			mlx_put_pixel(ptr, (int)x1, (int)y1, color);
		x1 += dx;
		y1 += dy;
	}
}*/


/*
int	ft_changed_resolution(t_data *data)
{
	if ((int)(data->mlx->width) != (int)(data->title.screen_width) || (int)(data->mlx->height) != (int)(data->title.screen_heigth))
	{
		data->title.screen_width = data->mlx->width;
		data->title.screen_heigth = data->mlx->height;
		return (1);
	}
	return (0);
}*/
