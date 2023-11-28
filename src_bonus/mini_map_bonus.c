/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:56:18 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/28 17:42:50 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		x = (data->px * data->scale_x) + (radio * cos(radianes));
		y = (data->py * data->scale_y) + (radio * sin(radianes));
		if (x > 0 && x < (int)(data->mlx->width * 0.3) && y > 0 && \
		y < (int)(data->mlx->height * 0.3))
			mlx_put_pixel(data->img[MINIMAP_GAME], x, y, 0xFFFFFFFF);
		angulo += 5;
	}
}

void	paint_square(int column, int row, int color, t_data *data)
{
	int	y;

	y = 0;
	while (y < (int)(data->mlx->height * 0.3) / data->map.height && \
	row * data->scale_y + \
	y < (int)(data->mlx->height * 0.3))
	{
		if ((column * data->scale_x) + data->scale_x <= \
		(int)(data->mlx->width * 0.3))
		{
			data->coord.x1 = column * data->scale_x;
			data->coord.y1 = row * data->scale_y + y;
			data->coord.x2 = (column * data->scale_x) + data->scale_x;
			data->coord.y2 = row * data->scale_y + y;
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
			if (data->map.map_aclean[y][x] == '1')
				paint_square(x, y, 0xFFFFFFFF, data);
			else if (ft_strchr("0OSEWNGBVZ", data->map.map_aclean[y][x]))
				paint_square(x, y, 0x000000FF, data);
			else if (data->map.map_aclean[y][x] == 'D' || \
			data->map.map_aclean[y][x] == '9')
				paint_square(x, y, 0x00FF00FF, data);
			else if (data->map.map_aclean[y][x] == 'A')
				paint_square(x, y, 0xFFFF00FF, data);
			x++;
		}
		y++;
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
		x = (data->steven_x * data->scale_x) + (radio * cos(radianes));
		y = (data->steven_y * data->scale_y) + (radio * sin(radianes));
		if (x > 0 && x < (int)(data->mlx->width * 0.3) && y > 0 && \
		y < (int)(data->mlx->height * 0.3))
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
