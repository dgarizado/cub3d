/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:47:32 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/04 19:42:35 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	msg_error(char *err)
{
	ft_putstr_fd(RED"Error\n"RST, 2);
	ft_putstr_fd(err, 2);
}

void	ft_error(char *err)
{
	ft_putstr_fd(RED"Error\n"RST, 2);
	ft_putstr_fd(err, 2);
	exit(1);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	**ft_abort(char **new_array, unsigned int i)
{
	while (i-- > 0)
		free(new_array[i]);
	free(new_array);
	return (0);
}

/**
 * @brief 
 * 
 * @param line 
 * @return int 0 is map 1 not map
 */
int	ft_ismap(char *line, char *str)
{
	int	flag;

	flag = 1;
	while (*line)
	{
		if (!ft_strchr(str, *line))
			flag = 0;
		line++;
	}
	return (flag);
}

double ft_degre_to_radian(double degre)
{
	double radian;

	radian = degre * M_PI / 180;
	return (radian);
}


