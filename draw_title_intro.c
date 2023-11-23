/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_title_intro.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:10:41 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/22 13:17:33 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_limits(int x, int y, t_data *data)
{
	if (x < 0 || x > WIDTH_IMG_TITLE)
		return (0);
	if (y < 0 || y > HEIGHT_IMG_TITLE)
		return (0);
	if (x + (WIDTH * 0.01) > WIDTH_IMG_TITLE || y + (WIDTH * 0.01) > HEIGHT_IMG_TITLE)
		return (0);
	return (1);
}

void	ft_draw_border(int x, int y, mlx_image_t *img, t_data *data)
{
	int	last_x;
	int	last_y;

	last_y = y + ((fabs)(HEIGHT_IMG_TITLE / data->title.heigth));
	last_x = x + ((fabs)(WIDTH_IMG_TITLE / data->title.length));
	if (check_limits(x, y, data) && check_limits(last_x, last_y, data))
	{
		drawLine(x, y, last_x, y, 0x000000FF, img, data);
		drawLine(x, y, x, last_y, 0x000000FF, img, data);
		drawLine(last_x, y, last_x, last_y, 0x000000FF, img, data);
		drawLine(x, last_y, last_x, last_y, 0x000000FF, img, data);
		drawLine(last_x, y, last_x + (WIDTH * 0.01), y + (WIDTH * 0.01), 0x000000FF, img, data);
		drawLine(last_x + (WIDTH * 0.01), y + (WIDTH * 0.01), last_x + (WIDTH * 0.01), last_y + (WIDTH * 0.01), 0x000000FF, img, data);
		drawLine(last_x, last_y, last_x + (WIDTH * 0.01), last_y + (WIDTH * 0.01), 0x000000FF, img, data);
		drawLine(x, last_y, x + (WIDTH * 0.01), last_y + (WIDTH * 0.01), 0x000000FF, img, data);
		drawLine(x + (WIDTH * 0.01), last_y + (WIDTH * 0.01), last_x + (WIDTH * 0.01), last_y + (WIDTH * 0.01), 0x000000FF, img, data);
	}
}

void	ft_draw_sq(mlx_image_t *img, t_data *data, int start_x, int start_y)
{
	t_coord *p;
	p = &data->coord;

	p->last_y = start_y + ((fabs)(HEIGHT_IMG_TITLE / data->title.heigth));
	p->last_x = start_x + ((fabs)(WIDTH_IMG_TITLE / data->title.length));
	p->y = start_y;
	while (p->y < p->last_y)
	{
		if (check_limits(start_x, start_y, data) && check_limits(p->last_x, p->last_y, data))
		{
			drawLine(start_x, p->y, p->last_x, p->y, set_color(p->y + data->title.color_up, data), img, data);
			drawLine(p->last_x, p->y, p->last_x + (WIDTH * 0.01), p->y + (WIDTH * 0.01), set_color(p->y + data->title.color_up, data), img, data);
		}
		p->y++;
	}
	p->x = start_x;
	while (p->x <= p->last_x)
	{
		if (check_limits(start_x, start_y, data) && check_limits(p->last_x, p->last_y, data))
			drawLine(p->x, p->y, p->x + (WIDTH * 0.01), p->y + (WIDTH * 0.01), set_color(p->y + data->title.color_up, data), img, data);
		p->x++;
	}
	ft_draw_border(start_x, start_y, img, data);
}

void	draw_square_img(t_data *data, int column, int row)
{
	int	x1;
	int	y1;

	x1 = column * (int)((WIDTH_IMG_TITLE / data->title.length));
	y1 = row * (int)((HEIGHT_IMG_TITLE / data->title.heigth));
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
