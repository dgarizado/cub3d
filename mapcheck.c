/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:00:58 by dgarizad          #+#    #+#             */
/*   Updated: 2023/10/22 21:05:02 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Parse the map by checking if all info elements are present and valid.
 * Also provides the real map array.
 * @param data 
 * @return true 
 * @return false 
 */
bool	ft_parse_info(t_data *data)
{
	int	i;

	i = 0;
	//HERE COMES THE FUNCTION FOR ELEMENTS
	ft_clean_map(data, 6); //Receives 6 from victor
	ft_check_chars(data);
	ft_map_anal(data);
	return (true);
}

/**
 * @brief Calculates the size of the buffer to read the map. 
 * Stores the map in the data structure data->map.map_s as a single string.
 * @param argv 
 * @param data 
 * @param fd 
 * @return true 
 * @return false 
 */
bool	ft_read_map(char **argv, t_data *data, int fd)
{
	int		i;

	i = 1;
	data->map.bytes = read(fd, data->map.map_s, BUFFER_SIZE);
	close(fd);
	if (data->map.bytes == -1 || data->map.bytes == 0)
	{
		free(data->map.map_s);
		ft_error(READ_ERR);
	}
	if (data->map.bytes < BUFFER_SIZE)
		data->map.map_s[data->map.bytes] = '\0';
	else
	{
		fd = open(argv[1], O_RDONLY);
		while (read(fd, data->map.map_s, BUFFER_SIZE) == BUFFER_SIZE)
			i++;
		data->map.bytes = i * BUFFER_SIZE;
		close(fd);
		free(data->map.map_s); //[1] Freed here
		data->map.map_s = ft_calloc(1, data->map.bytes); //[2] malloc Take care of this!!
		fd = open(argv[1], O_RDONLY);
		read(fd, data->map.map_s, data->map.bytes);
	}
	return (true);
}

/**
 * @brief This Section is for the mapcheck function
 * Check if the file is a .cub file and if it exists.
 * stores the map in data->map.map_a as an array of strings.
 * Also check if the map is valid.
 * @param argv 
 * @param data 
 * @return true 
 * @return false 
 */
bool	ft_mapcheck(char **argv, t_data *data)
{
	int	fd;

	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		ft_error(INPUT_EXT);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(INPUT_OPN);
	data->map.map_s = ft_calloc(1, BUFFER_SIZE); //[1] malloc Take care of this!!
	if (!data->map.map_s)
		ft_error("Malloc error\n");
	ft_read_map(argv, data, fd);
	data->map.map_a = ft_split(data->map.map_s, '\n'); //[3] malloc Take care of this!!
	if (!data->map.map_a)
		ft_error("Malloc error\n");
	if (data->map.map_a[0] == NULL || data->map.map_a[1] == NULL || data->map.map_a[2] == NULL) //HARDCODED
	{
		free(data->map.map_s);
		ft_abort(data->map.map_a, ft_arrlen(data->map.map_a)); //[2 and 3] Freed here
		ft_error("Map error\n");
	}
	ft_parse_info(data);
	return (true);
}
