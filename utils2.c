/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:41:11 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/15 13:52:08 by dgarizad         ###   ########.fr       */
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

/**
 * @brief This function is used to free all the pointers allocated
 * in the data structure regarding the map.
 * 
 * @param data 
 */
void	ft_free_maps(t_data *data)
{
	free(data->map.map_s);
	ft_abort(data->map.map_a, ft_arrlen(data->map.map_a)); //[2 and 3] Freed here
	free(data->map.map_sclean); //[4] Freed here
	ft_abort(data->map.map_aclean, ft_arrlen(data->map.map_aclean)); //[5] Freed here	
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