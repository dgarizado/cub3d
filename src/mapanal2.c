/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapanal2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:13:42 by dgarizad          #+#    #+#             */
/*   Updated: 2023/10/22 21:03:25 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if any 0 has a space on the right or left. 
 * or above or below. If so, it means that there is a walkable
 * zone not enclosed by walls.
 * @param data 
 */
void	ft_space_check_aux(t_data *data, int i, int j)
{
	if (data->map.map_aclean[i][j] == '0')
	{
		if (data->map.map_aclean[i][j + 1] == ' ' || \
		data->map.map_aclean[i][j - 1] == ' ' || \
		data->map.map_aclean[i + 1][j] == ' ' || \
		data->map.map_aclean[i - 1][j] == ' ')
		{
			ft_free_maps(data);
			ft_error("Map not enclosed by walls\n");
		}
	}
}
