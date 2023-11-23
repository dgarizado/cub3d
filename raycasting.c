/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:33:42 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/23 22:52:53 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	detras_de_steven_bonus( t_data *data, int n, float angle)
{
	if (data->cast.bonus.flag_bonus[n] == 'x' && data->cast.bonus.cell_step_bonus[n] == -1 && (data->cast.bonus.current_cell_bonus[n]) < (int)data->steven_x)
		return (1);
	else if (data->cast.bonus.flag_bonus[n] == 'x' && data->cast.bonus.cell_step_bonus[n] == 1 && (data->cast.bonus.current_cell_bonus[n]) > (int)data->steven_x)
		return (1);
	else if (data->cast.bonus.flag_bonus[n] == 'y' && data->cast.bonus.cell_step_bonus[n] == -1 && (data->cast.bonus.current_cell_bonus[n]) < (int)data->steven_y)
		return (1);
	else if (data->cast.bonus.flag_bonus[n] == 'y' && data->cast.bonus.cell_step_bonus[n] == 1 && (data->cast.bonus.current_cell_bonus[n]) > (int)data->steven_y)
		return (1);
	return (0);
}

void	drawline_game(double x1, double y1, double y2, t_data *data)
{
	double	dx;
	double	dy;
	double	steps;
	int color;

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

void	draw_colision(int rayCount, float angle, int n, t_data *data)
{
	int		colum_texture;
	int		wallheight;
	float	ray_end_x;
	float	ray_end_y;

	ray_end_x = data->px + (data->cast.bonus.distance[n] * cos((ft_degre_to_radian(angle))));
	ray_end_y = data->py + (data->cast.bonus.distance[n] * sin((ft_degre_to_radian(angle))));
	if (fabs(ray_end_x - round(ray_end_x)) > fabs(ray_end_y - round(ray_end_y)))
		//colum_texture = (int)(ray_end_x * 1000) % 1000;
		data->column_texture = (int)(ray_end_x * 1000) % 1000;
	else
		//colum_texture = (int)(ray_end_y * 1000) % 1000;
		data->column_texture = (int)(ray_end_y * 1000) % 1000;
	data->cast.bonus.distance[n] = fix_fish_eye(data->cast.bonus.distance[n], angle, data->angle);
	wallheight = floor(HEIGHT / 2) / data->cast.bonus.distance[n];
	if (last_colision_arr(data->cast.bonus.type_wall_bonus) == n)
	{
		data->map.flag = 0;
		drawline_game(rayCount, 0, (HEIGHT / 2) - wallheight, data);
		data->map.flag = 1;
		drawline_game(rayCount, (HEIGHT / 2) + wallheight, HEIGHT, data);
	}
	data->cast.bonus.n = n;
	//drawLineTexture_bonus(rayCount, (HEIGHT / 2) - wallheight, (HEIGHT / 2) + wallheight, colum_texture, data);
	drawLineTexture_bonus(rayCount, (HEIGHT / 2) - wallheight, (HEIGHT / 2) + wallheight, data);
}

void	draw_colisions(int rayCount, float angle, int flag, t_data *data)
{
	int	n;

	n = last_colision_arr(data->cast.bonus.type_wall_bonus);
	while (n >= 0)
	{
		if (detras_de_steven_bonus(data, n, angle) == flag)
			draw_colision(rayCount, angle, n, data);
		n--;
	}
}

void	raycast_game(mlx_image_t *game, t_data *data)
{
	float	increment_angle;
	float	angle;
	int		raycount;

	increment_angle = 60.0f / WIDTH;
	raycount = 0;
	angle = data->angle - 30;
	while (raycount < WIDTH)
	{
		ft_memset((&data->cast.bonus), 0, sizeof(t_bonus));
		rays(data->img[GAME], data, angle);
		draw_colisions(raycount++, angle, 1, data);
		angle += increment_angle;
	}
	draw_steven_sprite(data);
	raycount = 0;
	angle = data->angle - 30;
	while (raycount < WIDTH)
	{
		ft_memset((&data->cast.bonus), 0, sizeof(t_bonus));
		rays(data->img[GAME], data, angle);
		draw_colisions(raycount++, angle, 0, data);
		angle += increment_angle;
	}
}
