/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_title_intro_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:10:41 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/27 20:33:50 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_limits(int x, int y, t_data *data)
{
	if (x < 0 || x > data->mlx->width * 0.9)
		return (0);
	if (y < 0 || y > data->mlx->height * 0.4)
		return (0);
	if (x + (data->mlx->width * 0.01) > data->mlx->width * 0.9 || \
	y + (data->mlx->width * 0.01) > \
	data->mlx->height * 0.4)
		return (0);
	return (1);
}

void	ft_draw_sq(mlx_image_t *img, t_data *data, int start_x, int start_y)
{
	t_coord	*p;

	p = &data->coord;
	p->last_y = start_y + ((fabs)(data->mlx->height * \
	0.4 / data->title.heigth));
	p->last_x = start_x + ((fabs)(data->mlx->width * 0.9 / data->title.length));
	p->y = start_y;
	while (p->y < p->last_y)
	{
		if (check_limits(start_x, start_y, data) && check_limits(p->last_x, \
		p->last_y, data))
		{
			p->x1 = start_x;
			p->y1 = p->y;
			p->x2 = p->last_x;
			p->y2 = p->y;
			drawline(p, set_color(p->y + data->title.color_up, data), img, \
			data);
		}
		(p->y)++;
	}
}

void	draw_square_img(t_data *data, int column, int row)
{
	int	x1;
	int	y1;

	x1 = column * (int)((data->mlx->width * 0.9 / data->title.length));
	y1 = row * (int)((data->mlx->height * 0.4 / data->title.heigth));
	ft_draw_sq(data->img[TITLE_INTRO], data, x1, y1);
}

void	draw_title(t_data *data)
{
	int	row;
	int	column;

	row = 0;
	while (row < data->title.heigth)
	{
		column = 0;
		while (column < data->title.length)
		{
			if (data->title.arr[row][column] == '1')
				draw_square_img(data, column, row);
			column++;
		}
		row++;
	}
}
