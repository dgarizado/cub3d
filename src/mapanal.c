/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapanal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 23:57:37 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/27 20:35:58 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if any 0 is touching a space.
 * this would mean that there is a walkable zone not enclosed by walls.
 * Also checks if the player is enclosed by walls.
 * @param data 
 */
void	ft_space_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map.map_aclean[i])
	{
		while (data->map.map_aclean[i][j])
		{
			if (data->map.map_aclean[i][j] == '0' && (i == 0 || j == 0 || \
			(size_t)j == ft_strlen(data->map.map_aclean[i]) - 1 || \
			i == ft_arrlen(data->map.map_aclean) - 1))
			{
				ft_free_maps(data);
				ft_error("Bad map config\n");
			}
			ft_space_check_aux(data, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}

/**
 * @brief Creates a new str with the size given.
 * Fills the rest of the str with spaces.
 * 
 * @param str 
 * @param size 
 * @return char* 
 */
char	*ft_myrealloc(char *str, int size)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(char), (size + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	while (i < size)
	{
		new[i] = ' ';
		i++;
	}
	free(str);
	str = NULL;
	return (new);
}

/**
 * @brief Resizes the map to a square.
 * each line is resized to the longest line and filled with spaces.
 * Also stores the new width and height of the map.
 * @return true 
 * @return false 
 */
bool	ft_resize_aux(t_data *data, size_t max_len)
{
	int		i;

	i = 0;
	data->map.width = max_len;
	data->map.height = ft_arrlen(data->map.map_aclean);
	while (data->map.map_aclean[i])
	{
		if (ft_strlen(data->map.map_aclean[i]) < max_len)
		{
			data->map.map_aclean[i] = \
			ft_myrealloc(data->map.map_aclean[i], max_len);
		}
		i++;
	}
	return (true);
}

/**
 * @brief Iterates through the map and find the
 * longest line. In order to 
 * resize the map to a square.
 * @return true 
 * @return false 
 */
bool	ft_resize_map(t_data *data)
{
	int		i;
	int		j;
	size_t	max_len;

	i = 0;
	j = 0;
	max_len = 0;
	while (data->map.map_aclean[i])
	{
		while (data->map.map_aclean[i][j])
		{
			if (ft_strlen(data->map.map_aclean[i]) > max_len)
				max_len = ft_strlen(data->map.map_aclean[i]);
			j++;
		}
		j = 0;
		i++;
	}
	ft_resize_aux(data, max_len);
	return (true);
}

/**
 * @brief Resizes the map to a square.
 * Then analyzes if there are walkable
 * zones not enclosed by walls.
 * @param data 
 * @param queue 
 * @return int 
 */
bool	ft_map_anal(t_data *data)
{
	ft_resize_map(data);
	ft_space_check(data);
	return (true);
}
