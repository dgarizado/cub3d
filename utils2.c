/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:41:11 by dgarizad          #+#    #+#             */
/*   Updated: 2023/10/23 18:36:47 by dgarizad         ###   ########.fr       */
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
 * @brief This function is used to free all the pointers
 * in the data structure.
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
