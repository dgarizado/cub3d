/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 23:57:37 by dgarizad          #+#    #+#             */
/*   Updated: 2023/10/22 19:36:19 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief sets an array to keep track
 * of the "visited" nodes.
 * @param data 
 * @param queue 
 * @return int 
 */
int	ft_set_visited(t_data *data, t_queue *queue)
{
	int		i;
	char	*aux;

	aux = ft_strdup(data->map.map_sclean);
	i = 0;
	while (aux[i])
	{
		if (aux[i] != '1' && aux[i] != ' ' && aux[i] != '\n')
			aux[i] = 'N';
		i++;
	}
	queue->visited = ft_split(aux, '\n'); // [7] Malloc here
	free(aux);
	aux = NULL;
	ft_print_array(queue->visited);
	getchar();
	ft_add2queue(queue, data->player.y, data->player.x);
	ft_print_array(queue->visited);
	getchar();
	return (0);
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
 * @return true 
 * @return false 
 */
bool	ft_analyze_aux(t_data *data, size_t max_len)
{
	int		i;

	i = 0;
	while (data->map.map_aclean[i])
	{
		if (ft_strlen(data->map.map_aclean[i]) < max_len)
		{
			data->map.map_aclean[i] = ft_myrealloc(data->map.map_aclean[i], max_len);
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
bool ft_analyze_map(t_data *data)
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
	printf("max_len = %zu\n", max_len);
	getchar();
	ft_analyze_aux(data, max_len);
	return (true);
}

/**
 * @brief Applies the BFS algorithm to the map. 
 * for checking if the map is closed and there 
 * are spaces in the enclosed areas.
 * @param data 
 * @param queue 
 * @return int 
 */
bool	ft_bfs(t_data *data)
{
	t_queue	queue;
	
	printf("BFS\n");
	ft_bzero(&queue, sizeof(t_queue));
	queue.map_a = ft_split(data->map.map_sclean, '\n');	// [6] Malloc here
	//ft_set_visited(data, &queue);
	int i = 0;
	while (data->map.map_aclean[i])
	{
		printf("'%s'\n", data->map.map_aclean[i]);
		i++;
	}
	ft_analyze_map(data);
	i = 0;
	while (data->map.map_aclean[i])
	{
		printf("'%s'\n", data->map.map_aclean[i]);
		i++;
	}
	return (true);
}
