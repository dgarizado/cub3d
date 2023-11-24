/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:56:18 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/24 21:22:13 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_square(int column, int row, int color, t_data *data)
{
	int	y;

	y = 0;
	while (y < HEIGHT_MAP_GAME / data->map.height && row * SCALE_Y + \
	y < HEIGHT_MAP_GAME)
	{
		if ((column * SCALE_X) + SCALE_X <= WIDTH_MAP_GAME)
		{
			data->coord.x1 = column * SCALE_X;
			data->coord.y1 = row * SCALE_Y + y;
			data->coord.x2 = (column * SCALE_X) + SCALE_X;
			data->coord.y2 = row * SCALE_Y + y;
			drawline(&data->coord, color, data->img[MINIMAP_GAME], data);
		}
		y++;
	}
}

void	draw_squares(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.map_aclean[y][x] == '1' || \
			data->map.map_aclean[y][x] == '9' || \
			data->map.map_aclean[y][x] == 'D')
				paint_square(x, y, 0xFFFFFFFF, data);
			else if (ft_strchr("09DSEWNAGBVZ", data->map.map_aclean[y][x]))
				paint_square(x, y, 0x000000FF, data);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data, int radio)
{
	double	radianes;
	double	x;
	double	y;
	int		n;
	int		angulo;

	angulo = 0;
	n = 0;
	while (angulo <= 360)
	{
		radianes = angulo * (M_PI / 180.0);
		x = (data->px * SCALE_X) + (radio * cos(radianes));
		y = (data->py * SCALE_Y) + (radio * sin(radianes));
		if (x > 0 && x < WIDTH_MAP_GAME && y > 0 && y < HEIGHT_MAP_GAME)
			mlx_put_pixel(data->img[MINIMAP_GAME], x, y, 0xFFFFFFFF);
		angulo += 5;
	}
}

void	draw_steven(t_data *data, int radio)
{
	double	radianes;
	double	x;
	double	y;
	int		angulo;

	angulo = 0;
	while (angulo <= 360)
	{
		radianes = angulo * (M_PI / 180.0);
		x = (data->steven_x * SCALE_X) + (radio * cos(radianes));
		y = (data->steven_y * SCALE_Y) + (radio * sin(radianes));
		if (x > 0 && x < WIDTH_MAP_GAME && y > 0 && y < HEIGHT_MAP_GAME)
			mlx_put_pixel(data->img[MINIMAP_GAME], x, y, 0xFF0000FF);
		angulo += 10;
	}
}

void	ft_draw_minimap(t_data *data)
{
	draw_squares(data);
	draw_player(data, 5);
	draw_steven(data, 5);
	draw_raycast_map(data);
}
