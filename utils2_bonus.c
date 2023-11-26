/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:41:11 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/26 18:02:11 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"

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
	while (i < SPRITES_COUNT)
	{
		if (data->textures[i])
		{
			free(data->textures[i]->pixels);
			free(data->textures[i]);
		}
		i++;
	}
}
/**
 * @brief Here we load the png 
 * images of the walls and convert them to an mlx_texture_t
 * If all is ok this data->textures will be used
 * to create the images of the walls in the ft_load_minisprites function.
 * Also here we could check if the image has the correct size!
 * @param data 
 * @param flag 
 * @return true 
 * @return false 
 */
bool	ft_texture_parse(t_data *data, int flag)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(data->paths[flag]);
	if (texture == NULL)
	{
		return (false);
	}
	data->textures[flag] = texture;
	return (true);
}

/**
 * @brief This function is used to load the mini sprites
 * that will be used in the game. Wall textures
 * are treated appart just because they are not 
 * loaded in the same way.
 * Sprites are loaded individually
 * @param data 
 */
void	ft_load_minisprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < SPRITES_COUNT)
	{
		data->sprites[i] = mlx_texture_to_image(data->mlx, \
		data->textures[i]);
		i++;
	}
}
