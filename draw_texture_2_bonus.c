/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:11:23 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/26 18:01:26 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"

mlx_image_t	*choose_img_zombie(t_data *data)
{
	if ((mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT) \
	|| mlx_is_key_down(data->mlx, MLX_KEY_SPACE)) && aim_sprite(data))
		return(data->sprites[ENEMY2]);
	else
		return (data->sprites[ENEMY]);
}

uint32_t	apply_shading(t_data *data, uint8_t r, uint8_t g, uint32_t color)
{
	uint8_t	b;
	uint8_t	a;
	double	shading_factor;

	shading_factor = 1.0 - data->cast.bonus.distance[data->cast.bonus.n] / 10;
	if (shading_factor < 0.1)
		shading_factor = 0.1;
	r = (color >> 24) & 255;
	g = (color >> 16) & 255;
	b = (color >> 8) & 255;
	a = color & 255;
	r = (uint8_t)(r * shading_factor);
	g = (uint8_t)(g * shading_factor);
	b = (uint8_t)(b * shading_factor);
	a = (uint8_t)(a * shading_factor);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}