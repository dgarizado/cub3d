/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tittle_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:03:47 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/27 15:25:55 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*ft_cpy(char *buffer)
{
	int	fd;
	int	i;

	i = 1;
	fd = open("./map_title/title.fdf", O_RDONLY);
	while (read(fd, buffer, BUFFER_SIZE) == BUFFER_SIZE)
		i++;
	close(fd);
	free(buffer);
	buffer = ft_calloc(1, i * BUFFER_SIZE);
	fd = open("./map_title/title.fdf", O_RDONLY);
	read(fd, buffer, i * BUFFER_SIZE);
	close(fd);
	return (buffer);
}

char	*ft_cpy_title(void)
{
	int		fd;
	char	*buffer;
	int		bytes;
	int		i;

	i = 1;
	bytes = 1;
	fd = open("./map_title/title.fdf", O_RDONLY);
	if (!fd)
		msg_error("CANNOT OPEN MAP TITLE");
	buffer = ft_calloc(1, BUFFER_SIZE);
	bytes = read(fd, buffer, BUFFER_SIZE);
	close(fd);
	if (bytes <= 0)
	{
		free(buffer);
		buffer = NULL;
		ft_error("CANNOT READ MAP TITLE");
	}
	else
		buffer = ft_cpy(buffer);
	return (buffer);
}

char	*ft_parse_title(t_data *data)
{
	char	*buffer;

	buffer = ft_cpy_title();
	data->title.arr = ft_split(buffer, '\n');
	data->title.arr = ft_skip_sp_arr(data->title.arr);
	free(buffer);
	data->title.length = ft_strlen(data->title.arr[0]);
	data->title.heigth = ft_arrlen(data->title.arr);
	return (buffer);
}
