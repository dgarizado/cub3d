/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:53:05 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/14 23:07:24 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief check if * was freed. NO free(arr).
 */
void	ft_special_abort(char **arr, int i)
{
	while (i-- > 0)
	{
		if (arr[i] != NULL)
			free(arr[i]);
	}
}

/**
 * @brief check till line reached of the arr(map) just have  2 params per line.
 * @return int 0 KO. 1 OK
 */
int	ft_check_n_elem(t_data *data, int line_reached)
{
	char	**buffer;
	int		i;

	i = 0;
	while (i < line_reached)
	{
		buffer = ft_split(data->map.map_a[i], ' ');
		if (ft_arrlen(buffer) != 2)
		{
			msg_error("Nº PARAMETERS WRONG IN LINE\n");
			ft_abort(buffer, ft_arrlen(buffer));
			return (0);
		}
		ft_abort(buffer, ft_arrlen(buffer));
		i++;
	}
	return (1);
}

/**
 * @brief Converts all tab in single space.
 * @param data struct(data)->map.map_a(array of the map)
 * @return char** pointer to array converted. 
 */

void	*ft_swap_tabs_sp(char *str, char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr && arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == 9)
				arr[i][j] = 32;
			j++;
		}
		i++;
	}
	i = 0;
	while (str && str[i])
	{
		if (str[i] == 9)
			str[i] = 32;
		i++;
	}
	if (!str)
		return (arr);
	return (str);
}

void	ft_set_elements(char **elements)
{
	elements[0] = ft_strdup("NO");
	elements[1] = ft_strdup("SO");
	elements[2] = ft_strdup("WE");
	elements[3] = ft_strdup("EA");
	elements[4] = ft_strdup("F");
	elements[5] = ft_strdup("C");
	elements[6] = NULL;
}

/**
 * @brief  -set a array[7] with 6 diferents elements needed for the game.
 * 		   -swap all tabs to single space for easer parsing.
 * 		   -checks if there are all elements from array[7], no repeated, 
 * 			now we know n_lines = LINE_REACHED should check later.
 *		   -checks if all lines from 0 to LINE_REACHED just have 2 params.
 * 		   -checks if NO, SO, WE, EA paths till LINE_REACHED are ok.
 * 		   -checks if F, C colors till LINE_REACHED are ok.
 * @return int 0 = KO. 1 = OK (6 elements no repeat, 2 token per line, 
 * paths/color ok) 
 */
int	ft_parse_elements(t_data *data)
{
	char	*elements[7];
	int		line_reached;

	ft_set_elements(elements);
	data->map.map_a = (char **)ft_swap_tabs_sp(NULL, data->map.map_a);
	data->map.map_s = (char *)ft_swap_tabs_sp(data->map.map_s, NULL);
	line_reached = ft_check_elements(data, elements);
	if (line_reached <= 0 || !ft_check_n_elem(data, line_reached) || \
	!ft_check_paths(data, line_reached) || !ft_check_colors(data, line_reached))
		line_reached = 0;
	ft_special_abort(elements, ft_arrlen(elements));
	return (line_reached);
}
