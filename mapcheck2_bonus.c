/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:11:19 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/24 14:20:31 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Auxiliary function that
 * gets the player coords and help to check if there is only one.
 * Also sets the player angle.
 * Watchdog is used to check if there is only one player character.
 * @param i 
 * @param j 
 * @param data 
 * @param watchdog 
 */
void	get_player_coords(int i, int j, t_data *data, int *watchdog)
{
	if (ft_strchr("NWSE", data->map.map_aclean[i][j]) != NULL)
	{
		data->px = (double)(j + 0.5f);
		data->py = (double)(i + 0.5f);
		
		(*watchdog)++;
		//THIS IS THE NEW PART USING VICTORS	
		if (data->map.map_aclean[i][j] == 'N')
			data->angle = 270;
		if (data->map.map_aclean[i][j] == 'S')
			data->angle = 90;
		if (data->map.map_aclean[i][j] == 'W')
			data->angle = 180;
		if (data->map.map_aclean[i][j] == 'E')
			data->angle = 0;
	}
	if (ft_strchr("Z", data->map.map_aclean[i][j]) != NULL)
	{
		data->steven_x = (double)(j + 0.5f);
		data->steven_y = (double)(i + 0.5f);
		
		//THIS IS THE NEW PART USING VICTORS	
		if (data->map.map_aclean[i][j] == 'N')
			data->angle = 270;
		if (data->map.map_aclean[i][j] == 'S')
			data->angle = 90;
		if (data->map.map_aclean[i][j] == 'W')
			data->angle = 180;
		if (data->map.map_aclean[i][j] == 'E')
			data->angle = 0;
	}
}

void	ft_check_wd(t_data *data, int watchdog)
{
	if (watchdog != 1)
	{
		ft_free_maps(data);
		ft_error("Check player Character!\n");
	}
	//data->bonus = true;
}

/**
 * @brief Analyzes line by line the map and checks
 * if there is any character that is not 0, 1, N, S, W , E or space.
 * Bonus : D, X, O : Door, Enemy, Others
 * @param data 
 * @return true 
 * @return false 
 */
bool	ft_check_chars(t_data *data)
{
	int	i;
	int	watchdog;
	int	j;

	i = 0;
	j = 0;
	watchdog = 0;
	while (data->map.map_aclean[i] != NULL)
	{
		if (ft_ismap(data->map.map_aclean[i], "0 19BG5NWSEDXOZ") == 0)//CORREGUIR 
		{
			ft_free_maps(data);
			ft_error("Map is not valid\n");
		}
		while (data->map.map_aclean[i][j] != '\0')
		{
			get_player_coords(i, j, data, &watchdog);
			j++;
		}
		j = 0;
		i++;
	}
	ft_check_wd(data, watchdog);
	return (true);
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

	if (i > ft_arrlen(data->map.map_a) - 3 || i < 5)
	{
		free(data->map.map_s);
		ft_abort(data->map.map_a, ft_arrlen(data->map.map_a)); //[2 and 3] Freed here
		ft_error("Map is not valid, size");
	}
	data->map.map_aclean = ft_calloc(ft_arrlen(data->map.map_a) - i + 1, sizeof(char *));
	j = 0;
	while (j < ft_arrlen(data->map.map_a) - i)
	{
		data->map.map_aclean[j] = ft_strdup(data->map.map_a[i + j]);
		j++;
	}
	return (true);
}
