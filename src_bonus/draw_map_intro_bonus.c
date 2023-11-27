/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_intro_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:25:06 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/27 19:09:06 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	ft_draw_sq_map(t_data *data, int x1, int y1)
{
	int	x;
	int	y;
	int	z;

	y = y1;
	while (y <= (y1 + (HEIGTH_IMG_TITLE_MAP) * 0.4 / data->map.height))
	{
		x = x1;
		while (x <= (x1 + (WIDTH_IMG_TITLE_MAP) * 0.4 / data->map.width))
		{
			z = 0;
			while (z < (data->mlx->width * 0.005))
			{
				if (x - z++ < WIDTH_IMG_TITLE_MAP && x - z > 0 && y - z > 0 \
				&& y - z < HEIGTH_IMG_TITLE_MAP)
					mlx_put_pixel(data->img[MAP_INTRO], x - z, y - z, \
					0x9b9b9b80);
			}
			if (x - z < WIDTH_IMG_TITLE_MAP && x - z > 0 && y - z > 0 && y - z \
			< HEIGTH_IMG_TITLE_MAP)
				mlx_put_pixel(data->img[MAP_INTRO], x - z, y - z, 0x7e7e7e80);
			x++;
		}
		y++;
	}
}

static void	draw_sq_map_intro(t_data *data, int row, int column)
{
	int	dx;
	int	dy;
	int	width_mini_map;
	int	heigth_mini_map;

	dx = (int)((WIDTH_IMG_TITLE_MAP * 0.4) / data->map.width);
	dy = (int)((HEIGTH_IMG_TITLE_MAP * 0.4) / data->map.height);
	width_mini_map = data->map.width * dx * data->title.boom;
	heigth_mini_map = data->map.height * dy * data->title.boom;
	ft_draw_sq_map(data, ((WIDTH_IMG_TITLE_MAP / 2) - (width_mini_map / 2)) \
	+ (column * dx) * data->title.boom, ((HEIGTH_IMG_TITLE_MAP * 0.70) - \
	(heigth_mini_map / 2)) + (row * dy) * data->title.boom);
}

void	draw_title_map(t_data *d)
{
	int	row;
	int	column;

	row = 0;
	while (d->map.map_aclean[row])
	{
		column = 0;
		while (d->map.map_aclean[row][column])
		{
			if (d->map.map_aclean[row][column] == '1' || \
			d->map.map_aclean[row][column] == '9' || \
			d->map.map_aclean[row][column] == 'D')
				draw_sq_map_intro(d, row, column);
			column++;
		}
		row++;
	}
}
