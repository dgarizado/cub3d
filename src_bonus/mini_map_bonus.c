/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:56:18 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/27 20:32:56 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	paint_square(int column, int row, int color, t_data *data)
{
	int	y;
	int	scale_x;

	y = 0;
	scale_x = data->mlx->width * 0.3 / data->map.width;
	while (y < (int)data->mlx->height * 0.3 / data->map.height && \
	row * data->scale_y + \
	y < (int)data->mlx->height * 0.3)
	{
		if ((column * scale_x) + scale_x <= data->mlx->width * 0.3)
		{
			data->coord.x1 = column * scale_x;
			data->coord.y1 = row * data->scale_y + y;
			data->coord.x2 = (column * scale_x) + scale_x;
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
		x = (data->px * (int)data->mlx->width * 0.3 / data->map.width) \
		+ (radio * cos(radianes));
		y = (data->py * data->scale_y) + (radio * sin(radianes));
		if (x > 0 && x < data->mlx->width * 0.3 && \
		y > 0 && y < (int)data->mlx->height * 0.3)
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
		x = (data->steven_x * (int)data->mlx->width * 0.3 / data->map.width) \
		+ (radio * cos(radianes));
		y = (data->steven_y * data->scale_y) + (radio * sin(radianes));
		if (x > 0 && x < data->mlx->width * 0.3 && \
		y > 0 && y < (int)data->mlx->height * 0.3)
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
