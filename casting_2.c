/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:52:53 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/23 21:48:00 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	into_limits(t_data *data)
{
	if (0 <= data->cast.current_x_cell && 0 <= data->cast.current_y_cell && data->map.height > data->cast.current_y_cell && data->map.width > data->cast.current_x_cell)
		return (1);
	return (0);
}

int	get_value_map(t_data *data)
{
	return (data->map.map_aclean[data->cast.current_y_cell][data->cast.current_x_cell]);
}

void	set_params_colision(int n, t_data *data)
{
	data->cast.bonus.distance[n] = data->cast.ray_length;
	data->cast.bonus.cell_step_bonus[n] = data->cast.cell_step;
	data->cast.bonus.current_cell_bonus[n] = data->cast.current_cell;
	data->cast.bonus.flag_bonus[n] = data->cast.flag;
	data->cast.bonus.type_wall_bonus[n] = get_value_map(data);
}
