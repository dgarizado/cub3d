/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:11:19 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/01 20:42:41 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Auxiliary function that
 * gets the player coords and help to check if there is only one.
 * Also sets the player angle.
 * @param i 
 * @param j 
 * @param data 
 * @param watchdog 
 */
void	get_player_coords(int i, int j, t_data *data, int *watchdog)
{
	if (ft_strchr("NWSE", data->map.map_aclean[i][j]) != NULL)
	{
		data->player.x = j;
		data->player.y = i;
		data->player.pos.x = j;
		data->player.pos.y = i;
		(*watchdog)++;
		if (data->map.map_aclean[i][j] == 'N')
			data->player.angle = 90; // Pi/2
		if (data->map.map_aclean[i][j] == 'S')
			data->player.angle = 270; // 3Pi/2
		if (data->map.map_aclean[i][j] == 'W')
			data->player.angle = 180; // Pi
		if (data->map.map_aclean[i][j] == 'E')
			data->player.angle = 0; // 2Pi
		//THIS IS THE NEW PART USING VICTORS	
		if (data->map.map_aclean[i][j] == 'N')
			data->player.vdir.y = 1;
		if (data->map.map_aclean[i][j] == 'S')
			data->player.vdir.y = -1;
		if (data->map.map_aclean[i][j] == 'W')
			data->player.vdir.x = -1;
		if (data->map.map_aclean[i][j] == 'E')
			data->player.vdir.x = 1;
	}
}

void	ft_check_wd(t_data *data, int watchdog)
{
	if (watchdog != 1)
	{
		ft_free_maps(data);
		ft_error("Check player Character!\n");
	}
}

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
	int	j;

	i = 0;
	j = 0;
	watchdog = 0;
	while (data->map.map_aclean[i] != NULL)
	{
		if (ft_ismap(data->map.map_aclean[i], "0 1NWSE") == 0)
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
	int	firstlen;

	if (i > ft_arrlen(data->map.map_a) - 3 || i < 5)
	{
		free(data->map.map_s);
		ft_abort(data->map.map_a, ft_arrlen(data->map.map_a)); //[2 and 3] Freed here
		ft_error("Map is not valid");
	}
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
	return (true);
}
