/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_title_intro.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:10:41 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/20 20:16:44 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_limits(int x1, int y1, int last_x, int last_y, t_data *data)
{
	if (x1 < 0 || x1 > WIDTH_IMG_TITLE)
		return 0;
	if (y1 < 0 || y1 > HEIGHT_IMG_TITLE)
		return 0;
	if (last_x < 0 || last_x > WIDTH_IMG_TITLE)
		return 0;
	if (last_y < 0 || last_y > HEIGHT_IMG_TITLE)
		return 0;
	if (last_x + (WIDTH*0.01) > WIDTH_IMG_TITLE || last_y + (WIDTH*0.01) > HEIGHT_IMG_TITLE)
		return 0;
	return 1;
}

void	ft_draw_border(int x, int y, mlx_image_t*img,  t_data *data)
{
	int last_x;
	int last_y;

	last_y = y + ((fabs)(HEIGHT_IMG_TITLE / data->title.heigth));
	last_x = x + ((fabs)(WIDTH_IMG_TITLE / data->title.length));
	if (check_limits(x, y, last_x, last_y, data))
	{
		drawLine(x, y, last_x, y, 0x000000FF, img, data);
		drawLine(x, y, x, last_y, 0x000000FF, img, data);
		drawLine(last_x, y, last_x, last_y, 0x000000FF, img, data);
		drawLine(x, last_y, last_x, last_y, 0x000000FF, img, data);
		drawLine(last_x, y, last_x + (WIDTH*0.01), y+ (WIDTH*0.01), 0x000000FF, img, data);
		drawLine(last_x + (WIDTH*0.01), y + (WIDTH*0.01), last_x+ (WIDTH*0.01), last_y+ (WIDTH*0.01), 0x000000FF, img, data);
		drawLine(last_x, last_y, last_x+ (WIDTH*0.01), last_y + (WIDTH*0.01), 0x000000FF, img, data);
		drawLine(x, last_y, x + (WIDTH*0.01), last_y + (WIDTH*0.01), 0x000000FF, img, data);
		drawLine(x+ (WIDTH*0.01), last_y+ (WIDTH*0.01), last_x + (WIDTH*0.01), last_y + (WIDTH*0.01), 0x000000FF, img, data);
	}
}


void	ft_draw_sq(mlx_image_t* img, t_data *data, int x1, int y1)
{
	int x;
	int y;
	int last_x;
	int last_y;

	last_y = y1 + ((fabs)(HEIGHT_IMG_TITLE / data->title.heigth));
	last_x = x1 + ((fabs)(WIDTH_IMG_TITLE / data->title.length));
	y =y1;
	while(y < last_y)
	{
		if (check_limits(x1, y1, last_x, last_y, data))
		{
			drawLine(x1, y, last_x, y,  set_color(y + data->title.color_up, data), img, data);
			drawLine(last_x, y, last_x + (WIDTH*0.01), y + (WIDTH*0.01),  set_color(y + data->title.color_up, data), img, data);
		}
			y++;
	}
	x =x1;
	while(x <=last_x)
	{
		if (check_limits(x1, y1, last_x, last_y, data))
			drawLine(x, y, x + (WIDTH*0.01), y + (WIDTH*0.01),  set_color(y + data->title.color_up, data), img,data);
		x++;
	}
	ft_draw_border(x1, y1, img, data);
}

void draw_square_img(t_data * data, int column, int row)
{
	int x1;
	int y1;

	x1 = column * (int)((WIDTH_IMG_TITLE / data->title.length));
	y1 = row * (int)((HEIGHT_IMG_TITLE / data->title.heigth));
	ft_draw_sq(data->title.title_img, data, x1, y1);
}

 void draw_title(t_data * data)
 {
 	int row;
 	int column;

	row = 0;
	while(row < data->title.heigth)
	{
		 column = 0;
		 while(column < data->title.length)
		{
		 	if(data->title.arr[row][column] == '1')//TEMPORAL!!!
		 		draw_square_img(data, column, row);
		 	column++;
		}
		row++;
	}
}
