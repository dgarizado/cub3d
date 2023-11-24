/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:44:33 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/24 22:26:49 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_last_colision(float cell, int cell_step, char flag, t_data *d)
{
	d->cast.current_cell = cell;
	d->cast.cell_step = cell_step;
	d->cast.flag = flag;
}

void	set_new_instances(t_data *d)
{
	if (d->cast.ray_x_length < d->cast.ray_y_length)
	{
		d->cast.ray_length = d->cast.ray_x_length;
		d->cast.ray_x_length += d->cast.ray_x_unit_length;
		d->cast.current_x_cell += d->cast.cell_x_step;
		save_last_colision(d->cast.current_x_cell, d->cast.cell_x_step, 'x', d);
	}
	else if (d->cast.ray_x_length > d->cast.ray_y_length)
	{
		d->cast.ray_length = d->cast.ray_y_length;
		d->cast.ray_y_length += d->cast.ray_y_unit_length;
		d->cast.current_y_cell += d->cast.cell_y_step;
		save_last_colision(d->cast.current_y_cell, d->cast.cell_y_step, 'y', d);
	}
	else
	{
		d->cast.ray_length = d->cast.ray_x_length;
		d->cast.ray_x_length += d->cast.ray_x_unit_length;
		d->cast.ray_y_length += d->cast.ray_y_unit_length;
		d->cast.current_x_cell += d->cast.cell_x_step;
		d->cast.current_y_cell += d->cast.cell_y_step;
		save_last_colision(d->cast.current_y_cell, d->cast.cell_y_step, 'y', d);
	}
}

void	set_direction_and_ray_length(t_data *data)
{
	if (data->cast.ray_x_direction <= 0)
	{
		data->cast.cell_x_step = -1;
		data->cast.ray_x_length = data->cast.ray_x_unit_length * \
		(data->cast.ray_x_start - data->cast.current_x_cell);
	}
	else if (data->cast.ray_x_direction > 0)
	{
		data->cast.cell_x_step = 1;
		data->cast.ray_x_length = data->cast.ray_x_unit_length * \
		((1 + data->cast.current_x_cell) - data->cast.ray_x_start);
	}
	if (data->cast.ray_y_direction <= 0)
	{
		data->cast.cell_y_step = -1;
		data->cast.ray_y_length = data->cast.ray_y_unit_length * \
		(data->cast.ray_y_start - data->cast.current_y_cell);
	}
	else if (data->cast.ray_y_direction > 0)
	{
		data->cast.cell_y_step = 1;
		data->cast.ray_y_length = data->cast.ray_y_unit_length * \
		((1 + data->cast.current_y_cell) - data->cast.ray_y_start);
	}
}

void	set_params_start_cast(float angle, t_data *data)
{
	data->cast.ray_length = 0;
	data->cast.cell_x_step = 0;
	data->cast.cell_y_step = 0;
	data->cast.ray_x_start = data->px;
	data->cast.ray_y_start = data->py;
	data->cast.ray_x_direction = cos(ft_degre_to_radian(angle));
	data->cast.ray_y_direction = sin(ft_degre_to_radian(angle));
	data->cast.ray_x_unit_length = sqrt(1 + pow(data->cast.ray_y_direction / \
	data->cast.ray_x_direction, 2));
	data->cast.ray_y_unit_length = sqrt(1 + pow(data->cast.ray_x_direction / \
	data->cast.ray_y_direction, 2));
	data->cast.ray_x_length = 0;
	data->cast.ray_y_length = 0;
	data->cast.current_x_cell = floor(data->cast.ray_x_start);
	data->cast.current_y_cell = floor(data->cast.ray_y_start);
}

float	rays(t_data *data, float angle)
{
	int		n;
	char	c;

	n = 0;
	set_params_start_cast(angle, data);
	set_direction_and_ray_length(data);
	while (1)
	{
		set_new_instances(data);
		if (into_limits(data))
		{
			c = get_value_map(data);
			if (c == '1' || c == '9' || c == 'D')
			{
				set_params_colision(n, data);
				break ;
			}
			else if (c == 'B' || c == 'O' || c == 'V' || c == 'G' || c == 'A')
			{
				if (n < 8)
					set_params_colision(n++, data);
			}
		}
	}
	return (data->cast.ray_length);
}
