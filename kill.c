/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:09:50 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/25 18:36:06 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_kill_steven(t_data *d)
{
	static int	n = 1;
	static int	life;
	
	life++;
	if (life >= 10)
	{
		d->steven_x = d->stv_x[n];
		d->steven_y = d->stv_y[n];
		if (d->stv_x[n + 1] != 0)
			n++;
		else
		{
			d->steven_x = 1000;
			d->steven_y = 1000;	
		}
		life = 0;	
	}
}

int	aim_sprite(t_data *data)
{
	double	angle_steven_from_me;
	double	angulo_me;
	double  max;

	angle_steven_from_me = data->angle_steven - 180;
	angulo_me = data->angle - 15;
	max =fmod(angulo_me + 15, 360);
	normalize_angle(&angulo_me, &angle_steven_from_me);
	printf("zombie look %f, me -> %f\n", angle_steven_from_me, angulo_me);
	while (angulo_me < max)
	{
		if (almost_equal(angulo_me, angle_steven_from_me) == 1)
			return (1);
		angulo_me = angulo_me + 0.01;
		normalize_angle(&angulo_me, &angle_steven_from_me);
	}
	return (0);
}

void ft_kill(t_data	*data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE) || (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT)))
	{
		data->sprites[PISTOL]->instances[0].enabled = false;
		data->sprites[PISTOL_BANG]->instances[0].enabled = true;
		if(aim_sprite(data))
			ft_kill_steven(data);
	}
}