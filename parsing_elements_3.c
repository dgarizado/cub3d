/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:21:29 by vcereced          #+#    #+#             */
/*   Updated: 2023/10/22 20:11:52 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_rgb(char *token)
{
	char	**buff;
	int		i;

	i = 0;
	buff = ft_split(token, ',');
	while (ft_arrlen(buff) == 3 && buff[i])
	{
		if (!(ft_atoi(buff[i]) >= 0 && ft_atoi(buff[i]) <= 255))
			break ;
		i++;
	}
	ft_abort(buff, ft_arrlen(buff));
	if (i == 3)
		return (1);
	return (0);
}

int	ft_check_color(char **buff)
{
	int	flag;

	flag = 0;
	if (buff[0][0] == 'F' && buff[0][1] == '\0' \
	&& ft_ismap(buff[1], "0123456789,"))
		flag = ft_check_rgb(buff[1]);
	else if (buff[0][0] == 'C' && buff[0][1] == '\0' \
	&& ft_ismap(buff[1], "0123456789,"))
		flag = ft_check_rgb(buff[1]);
	return (flag);
}

/**
 * @brief check the color of C and F. 
 * 			-iter till line_reached
 * 				--token line with split
 * 					---check 1º token is F or C
 * 					---check 2º token color ok
 * 				--every time thats ok the cont. increment
 * @return int 1 OK (2 colors). 0 KO (color != 2).
 */
int	ft_check_colors(t_data *data, int line_reached)
{
	char	**buffer;
	int		i;
	int		status;
	int		cont;

	cont = 0;
	i = 0;
	while (i < line_reached)
	{
		buffer = ft_split(data->map.map_a[i], ' ');
		status = ft_check_color(buffer);
		if (status == 1)
			cont++;
		ft_abort(buffer, ft_arrlen(buffer));
		i++;
	}
	if (cont == 2)
		return (1);
	msg_error("RGB WRONG\n");
	return (0);
}

/**
 * @brief check if NO, SO, WE, EA paths are ok.
 * @param buffer tokenized line of the arr(map).
 * @return int <= 0 KO (cannot open/path wrong). >1 OK.
 */
int	ft_check_path(char **bf)
{
	int	flag;
	int	fd;

	flag = 0;
	if (((bf[0][0] == 'N' && bf[0][1] == 'O' ) || (bf[0][0] == 'N' \
	&& bf[0][1] == '\0')) && bf[1][0] == '.' && bf[1][1] == '/')
		flag = 1;
	else if (((bf[0][0] == 'S' && bf[0][1] == 'O') || (bf[0][0] == 'S' \
	&& bf[0][1] == '\0')) && bf[1][0] == '.' && bf[1][1] == '/')
		flag = 1;
	else if (((bf[0][0] == 'W' && bf[0][1] == 'E') || (bf[0][0] == 'W' \
	&& bf[0][1] == '\0')) && bf[1][0] == '.' && bf[1][1] == '/')
		flag = 1;
	else if (((bf[0][0] == 'E' && bf[0][1] == 'A') || (bf[0][0] == 'E' \
	&& bf[0][1] == '\0')) && bf[1][0] == '.' && bf[1][1] == '/')
		flag = 1;
	if (flag == 1)
	{
		fd = open(bf[1], O_RDONLY);
		close(fd);
		flag = fd;
	}
	return (flag);
}

/**
 * @brief checking paths of elements. NO CHECKS IF ELEMENTS ARE REPEATED.
 * 			-iter till line_reached
 * 				--token the line with split
 * 					---checks 1º token (NO, SO, WE, EA) and 2º token (./...) are ok.
 * 					---checks path of the 2ºtoken.
 * @return int 1 OK (4 paths are ok). 0 KO(more/less paths/no open).
 */
int	ft_check_paths(t_data *data, int line_reached)
{
	char	**buffer;
	int		i;
	int		cont;

	cont = 0;
	i = 0;
	while (i < line_reached)
	{
		buffer = ft_split(data->map.map_a[i], ' ');
		if (ft_check_path(buffer) > 0)
			cont++;
		ft_abort(buffer, ft_arrlen(buffer));
		i++;
	}
	if (cont == 4)
		return (1);
	msg_error("PATH WRONG\n");
	return (0);
}
