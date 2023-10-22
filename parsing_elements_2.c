/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:40:15 by vcereced          #+#    #+#             */
/*   Updated: 2023/10/22 19:39:07 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief iter the array of elements. check any not NULL
 * @return int 0 all NULL. !0 any not NULL
 */
int	ft_miss_elements(char **elements)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (elements[i] != NULL)
			return (1);
		i++;
	}
	return (0);
}

/**
 *@brief	-iter 7 times cuz should 6 elements in the game.
 				--compare 1º token with the array of elements.
 * 					---when occur free element, point to NULL so cannot macht 
again if any repeat. 	
 * @return int 1 OK. 0 KO (any not encounter/repeat).
 */
int	ft_check_buffer(char *token, char **elements)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (elements[i] && !ft_strncmp(token, elements[i], ft_strlen(token)))
		{
			free(elements[i]);
			elements[i] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief 	-iter the array(map) and checks is part of map. 
 * 			-token the line.
 * 			-compare the token[0] with list of elements.
 * 				--elements occurs is erased from the list so any repeated 
 * 				  cannot match.
 *			-check if any elements not occur.
 * @param elements list of elements.
 * @return int 0  if any elements is repeat. -1 if miss any elements. n > 0 
 * line reached in the arrayshould the map from here. 
 */
int	ft_check_elements(t_data *data, char **elements)
{
	int		line_reached;
	char	**buffer;
	int		i;

	i = 0;
	line_reached = 0;
	while (*(data->map.map_a[line_reached]) && \
	!ft_ismap(data->map.map_a[line_reached], " 01NWSE"))
	{
		buffer = ft_split(data->map.map_a[line_reached], ' ');
		if (!ft_check_buffer(buffer[0], elements))
		{
			ft_abort(buffer, ft_arrlen(buffer));
			return (0);
		}
		ft_abort(buffer, ft_arrlen(buffer));
		line_reached++;
	}
	if (ft_miss_elements(elements))
		line_reached = -1;
	return (line_reached);
}
