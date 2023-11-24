/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:33:42 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/24 21:09:56 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	detras_de_steven_bonus(t_data *d, int n)
{
	if (d->cast.bonus.flag_bonus[n] == 'x' && d->cast.bonus.cell_step_bonus[n] == -1 && (d->cast.bonus.current_cell_bonus[n]) < (int)d->steven_x)
		return (1);
	else if (d->cast.bonus.flag_bonus[n] == 'x' && d->cast.bonus.cell_step_bonus[n] == 1 && (d->cast.bonus.current_cell_bonus[n]) > (int)d->steven_x)
		return (1);
	else if (d->cast.bonus.flag_bonus[n] == 'y' && d->cast.bonus.cell_step_bonus[n] == -1 && (d->cast.bonus.current_cell_bonus[n]) < (int)d->steven_y)
		return (1);
	else if (d->cast.bonus.flag_bonus[n] == 'y' && d->cast.bonus.cell_step_bonus[n] == 1 && (d->cast.bonus.current_cell_bonus[n]) > (int)d->steven_y)
		return (1);
	return (0);
}

void	drawline_game(double x1, double y1, double y2, t_data *data)
{
	double	dx;
	double	dy;
	double	steps;
	int		color;

	dy = y2 - y1;
	steps = fabs(dy);
	dx = 0 / steps;
	dy = dy / steps;
	if (data->map.flag == 0)
		color = data->map.colors[CEILING];
	else
		color = data->map.colors[FLOOR];
	while ((int)fabs(y2 - y1))
	{
		if (x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
			mlx_put_pixel(data->img[GAME], (int)x1, (int)y1, color);
		x1 += dx;
		y1 += dy;
	}
}

void	draw_colision(int rayCount, float a, int n, t_data *data)
{

	int		wallheight;
	float	endx;
	float	endy;

	endx = data->px + data->cast.bonus.distance[n] * cos(ft_degre_to_radian(a));
	endy = data->py + data->cast.bonus.distance[n] * sin(ft_degre_to_radian(a));
	if (fabs(endx - round(endx)) > fabs(endy - round(endy)))
		data->column_texture = (int)(endx * 1000) % 1000;
	else
		data->column_texture = (int)(endy * 1000) % 1000;
	data->cast.bonus.distance[n] = fix_fish_eye(data->cast.bonus.distance[n], \
	a, data->angle);
	wallheight = floor(HEIGHT / 2) / data->cast.bonus.distance[n];
	if (last_colision_arr(data->cast.bonus.type_wall_bonus) == n)
	{
		data->map.flag = 0;
		//drawline_game(rayCount, 0, (HEIGHT / 2) - wallheight, data);
		drawline_game(rayCount, 0, (HEIGHT / 2) - wallheight + data->up, data);
		data->map.flag = 1;
		//drawline_game(rayCount, (HEIGHT / 2) + wallheight, HEIGHT, data);
		drawline_game(rayCount, (HEIGHT / 2) + wallheight - data->up, HEIGHT, data);
	}
	data->cast.bonus.n = n;
	//drawlinetexture_bonus(rayCount, (HEIGHT / 2) - wallheight, (HEIGHT / 2) \
	+ wallheight, data);
	drawlinetexture_bonus(rayCount, (HEIGHT / 2) - wallheight - data->up, (HEIGHT / 2) + wallheight - data->up, data);
}

void	draw_colisions(int rayCount, float angle, int flag, t_data *data)
{
	int	n;

	n = last_colision_arr(data->cast.bonus.type_wall_bonus);
	while (n >= 0)
	{
		if (detras_de_steven_bonus(data, n) == flag || data->zombie == 0)
			draw_colision(rayCount, angle, n, data);
		n--;
	}
}

void	raycast_game(t_data *data)
{
	float	increment_angle;
	float	angle;
	int		raycount;

	increment_angle = 60.0f / WIDTH;
	raycount = 0;
	angle = data->angle - 30;
	encounter_steven(data);
	while (raycount < WIDTH)
	{
		ft_memset((&data->cast.bonus), 0, sizeof(t_bonus));
		rays(data, angle);
		draw_colisions(raycount++, angle, 1, data);
		angle += increment_angle;
	}
	if (data->zombie == 1)
	{
		draw_steven_sprite(data);
		raycount = 0;
		angle = data->angle - 30;
		while (raycount < WIDTH)
		{
			ft_memset((&data->cast.bonus), 0, sizeof(t_bonus));
			rays(data, angle);
			draw_colisions(raycount++, angle, 0, data);
			angle += increment_angle;
		}
	}
}
