/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapanal2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:13:42 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/26 18:01:15 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"

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
