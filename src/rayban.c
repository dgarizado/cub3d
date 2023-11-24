/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayban.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:02:13 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/23 20:35:32 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief This function is used to rotate a victor
 * relative to the origin of the map.
 * receives a vector and an angle in radians
 * modifies x and y of the vector into the new coordinates
 * that the vector will have after rotation.
 * @param victor 
 * @param angle 
 */
void	rotate_victor(t_victor *victor, double angle)
{
	double	x;
	double	y;

	x = victor->x;
	y = victor->y;
	victor->x = x * cos(angle * M_PI / 180) - y * sin(angle * M_PI / 180);
	victor->y = x * sin(angle * M_PI / 180) + y * cos(angle * M_PI / 180);
}

void	ray_checkwall(t_data *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.sidedistx < data->ray.sidedisty)
		{
			data->ray.sidedistx += data->ray.deltadistx;
			data->ray.mapx += data->ray.stepx;
			data->ray.side = TEX_E;
			if (data->ray.stepx == -1)
				data->ray.side = TEX_W;
		}
		else
		{
			data->ray.sidedisty += data->ray.deltadisty;
			data->ray.mapy += data->ray.stepy;
			data->ray.side = TEX_S;
			if (data->ray.stepy == -1)
				data->ray.side = TEX_N;
		}
		if (data->ray.mapx >= 0 && data->ray.mapx < data->map.width && \
		data->ray.mapy >= 0 && data->ray.mapy < data->map.height)
		{
			if (data->map.map_aclean[data->ray.mapy][data->ray.mapx] == '1')
				data->ray.hit = 1;
		}
	}
}

void	ray_checkdir(t_data *data)
{
	if (data->ray.raydirx < 0)
	{
		data->ray.stepx = -1;
		data->ray.sidedistx = (data->player.pos.x - data->ray.mapx) * \
		data->ray.deltadistx;
	}
	else
	{
		data->ray.stepx = 1;
		data->ray.sidedistx = (data->ray.mapx + 1.0 - data->player.pos.x) * \
		data->ray.deltadistx;
	}
	if (data->ray.raydiry < 0)
	{
		data->ray.stepy = -1;
		data->ray.sidedisty = (data->player.pos.y - data->ray.mapy) * \
		data->ray.deltadisty;
	}
	else
	{
		data->ray.stepy = 1;
		data->ray.sidedisty = (data->ray.mapy + 1.0 - data->player.pos.y) * \
		data->ray.deltadisty;
	}
}

/**
 * @brief Here we update
 * the ray direction according to the pixel we are drawing
 * and the player position. 
 * 
 * @param data 
 */
void	ray_update(t_data *data)
{
	data->ray.camerax = 2 * data->ray.x / \
	(double)(data->map.width * data->map.ppc) - 1;
	data->ray.raydirx = data->player.vdir.x + \
	data->player.plane.x * data->ray.camerax;
	data->ray.raydiry = data->player.vdir.y + \
	data->player.plane.y * data->ray.camerax;
	data->ray.mapx = (int)data->player.pos.x;
	data->ray.mapy = (int)data->player.pos.y;
	if (data->ray.raydirx == 0)
		data->ray.raydirx = 0.001;
	if (data->ray.raydiry == 0)
		data->ray.raydiry = 0.001;
	data->ray.deltadistx = fabs(1 / data->ray.raydirx);
	data->ray.deltadisty = fabs(1 / data->ray.raydiry);
	data->ray.hit = 0;
}

void	ray_bang(t_data *data)
{
	data->ray.x = 0;
	while (data->ray.x < data->map.mlx->width)
	{
		ray_update(data);
		ray_checkdir(data);
		ray_checkwall(data);
		ray_render(data);
		data->ray.x++;
	}
}
