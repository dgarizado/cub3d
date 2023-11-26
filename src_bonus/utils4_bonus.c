/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:12:01 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/26 18:02:16 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"

double	radian_to_grade(double radianes)
{
	double	grados;

	grados = radianes * (180.0 / M_PI);
	grados = fmod(grados, 360.0);
	if (grados < 0)
		grados += 360.0;
	return (grados);
}

double	ft_degre_to_radian(double degre)
{
	double	radian;

	radian = degre * (M_PI / 180);
	return (radian);
}

float fix_fish_eye(float distance, float angle, float angle_player)
{
	distance = distance * cos(ft_degre_to_radian(angle - angle_player));
	return (distance);
}

void	ft_skip_sp_arr2(char **arr, int *len)
{
	int		i;
	int		j;
	int		n;
	char	*buffer;

	i = 0;
	while (arr[i])
	{
		j=0;
		n = 0;
		buffer = (char *)calloc(*len + 1,  1);
		while (arr[i][n])
		{
			if(ft_isdigit(arr[i][n]))
			buffer[j++] = arr[i][n];
			n++;
		}
		free(arr[i]);
		arr[i] = buffer;
		i++;
	}
}

char **ft_skip_sp_arr(char **arr)
{
	int i;
	int len;
	
	len = 0;
	i = 0;
	while(arr[0][i])
	{
		if(ft_isdigit(arr[0][i]))
			len++;
		i++;
	}
	i = 0;
	ft_skip_sp_arr2(arr, &len);
	return(arr);
}
