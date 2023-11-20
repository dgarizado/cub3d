/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureparsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:48:22 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/17 13:33:15 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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