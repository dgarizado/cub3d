/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:11:19 by dgarizad          #+#    #+#             */
/*   Updated: 2023/10/22 00:16:59 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//DELETE THIS UNTIL MERGE WITH VICTOR
int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

int ft_ismap(char *line)
{
    int flag;
    flag = 1;
    while(*line)
    {
        if(!ft_strchr("0 1NWSE", *line))
            flag = 0;
        line++;
    }
    return(flag);
}

//DELETE THIS UNTIL MERGE WITH VICTOR
/**
 * @brief Analyzes line by line the map and checks
 * if there is any character that is not 0, 1, N, S, W , E or space.
 * 
 * @param data 
 * @return true 
 * @return false 
 */
bool	ft_check_chars(t_data *data)
{
	int	i;
	int	watchdog;
	int j;

	i = 0;
	j = 0;
	watchdog = 0;
	while (data->map.map_aclean[i] != NULL)
	{
		if (ft_ismap(data->map.map_aclean[i]) == 0)
			ft_error("Map is not valid\n");
		while (data->map.map_aclean[i][j] != '\0')
		{
			if (ft_strchr("NWSE", data->map.map_aclean[i][j]) != NULL)
				watchdog++;
			j++;
		}
		j = 0;
		i++;
	}
	if (watchdog != 1)
		ft_error("Character Problems!\n");
	return	(true);
}

/**
 * @brief Receives the index of the line where the map starts
 * and creates a new array with the map only.
 * 
 * @param data 
 * @param i 
 * @return true 
 * @return false 
 */
bool	ft_clean_map(t_data *data, int i)
{
	int	j;
	int	firstlen;
	
	if (i > ft_arraylen(data->map.map_a) - 3 || i < 5)
		ft_error("Map is not valid");
	j = 0;
	firstlen = 0;
	while (j < i)
	{
		firstlen += ft_strlen(data->map.map_a[j]) + 1;
		j++;
	}
	j = firstlen;
	data->map.map_sclean = ft_strdup(data->map.map_s + firstlen); //[4] malloc Take care of this!!
	data->map.map_aclean = ft_split(data->map.map_sclean, '\n'); //[5] malloc Take care of this!!
	ft_print_array(data->map.map_aclean);
	return (true);
}
