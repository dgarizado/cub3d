/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:42:12 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/27 19:10:15 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	raycast_game_aux(t_data *data)
{
	float	increment_angle;
	float	angle;
	int		raycount;

	increment_angle = 60.0f / data->mlx->width;
	if (data->zombie == 1)
	{
		draw_steven_sprite(data);
		raycount = 0;
		angle = data->angle - 30;
		while (raycount < data->mlx->width)
		{
			ft_memset((&data->cast.bonus), 0, sizeof(t_bonus));
			rays(data, angle);
			draw_colisions(raycount++, angle, 0, data);
			angle += increment_angle;
		}
	}
}
