/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 00:47:57 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/22 11:15:46 by vcereced         ###   ########.fr       */
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

void draw_start(double x1, double y1, double x2, double y2, int column_texture, t_data *data)
{
	double dx = x2 - x1;//pantalla
	double dy =  y2 -y1;//pantalla y significa WALL-HEIGHT y esta distancia es la que hay que pintar el sprite proporcionalmente
	double steps;
	int row_texture = 0;//textura
	uint32_t color;

	if ((abs)((int)dx) >= (abs)((int)dy))
		steps = (fabs)(dx);//pantalla
	float step_y_texture = (float)data->sprites[START_INTRO]->height/(float)steps;
	dx = dx / steps;//pantalla
	dy = dy / steps;//pantalla es 1 pa la textura
	int n = 0;
	
	while ((int)fabs(x2 - x1) || (int)fabs(y2 - y1))
	{
		row_texture = floor(step_y_texture * n++);
		if(x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
		{
			color = ((uint32_t*)data->sprites[START_INTRO]->pixels)[row_texture * data->sprites[START_INTRO]->width + column_texture];
			if(color != 0)
				//((uint32_t*)data->title.title_map->pixels)[((int)y1 * data->title.title_map->width + (int)x1)] = color;
				((uint32_t*)data->img[MAP_INTRO]->pixels)[((int)y1 * data->img[MAP_INTRO]->width + (int)x1)] = color;
		}
		x1 += dx;
		y1 += dy;
	}
}

void	ft_draw_start_texture(float wallheight, float wallweight, float column, t_data *data)
{
	int		n;
	int		column_texture;
	float	increment_texture_column;

	n = 0.0;
	column_texture = 0;
	column = column - (wallweight / 2);
	increment_texture_column = data->sprites[START_INTRO]->width / wallweight;

	while (column_texture < data->sprites[START_INTRO]->width)
	{
		column_texture = increment_texture_column * n;
		draw_start(column, (HEIGHT *0.4) , column, (HEIGHT *0.4) + (wallheight), (int)column_texture, data);
		n++;
		column++;
	}
}
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
