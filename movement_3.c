/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:24:47 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/25 18:25:39 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_step(t_data *d)
{
	static double pasos;
	
	if (mlx_is_key_down(d->mlx, MLX_KEY_W) || \
	mlx_is_key_down(d->mlx, MLX_KEY_A) || \
	mlx_is_key_down(d->mlx, MLX_KEY_S) || mlx_is_key_down(d->mlx, MLX_KEY_D))
		d->up = abs((int)(15 * sin(pasos++ * 0.2)));
}
void ft_check_win(t_data *data)
{
	static int pas = 0;
	if (data->map.map_aclean[(int)(data->py)][(int)(data->px)] == 'A')
	{
			data->up = abs((int)(100 * sin(pas * 0.2)));
			pas++;
	}
}
