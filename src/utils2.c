/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:41:11 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/26 18:53:17 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//DELETE THIS AT THE END OF THE PROJECT
void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_putstr_fd(array[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
//DELETE THIS AT THE END OF THE PROJECT

uint32_t	apply_shading(t_data *data, uint8_t r, uint8_t g, uint32_t color)
{
	uint8_t	b;
	uint8_t	a;
	double	shading_factor;

	shading_factor = 1.0 - data->ray.perpwalldist / 25;
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

/**
 * @brief This function is used to free all the pointers allocated
 * in the data structure regarding the map.
 * 
 * @param data 
 */
void	ft_free_maps(t_data *data)
{
	free(data->map.map_s);
	ft_abort(data->map.map_a, ft_arrlen(data->map.map_a));
	free(data->map.map_sclean);
	ft_abort(data->map.map_aclean, ft_arrlen(data->map.map_aclean));
}

/**
 * @brief Textures are allocated in the mlx_load_png function
 * and then converted to images in the mlx_texture_to_image function.
 * they also allocate memory for the pixels.
 * 
 * @param data 
 */
void	ft_free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (data->textures[i])
		{
			free(data->textures[i]->pixels);
			free(data->textures[i]);
		}
		i++;
	}
}
