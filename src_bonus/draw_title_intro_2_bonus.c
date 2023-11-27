/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_title_intro_2_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 00:19:52 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/27 19:29:27 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	range_up(int start)
{
	if (start >= 350)
		return (0x778899);
	else if (start >= 300)
		return (0xBA55D3FF);
	else if (start >= 250)
		return (0xFFA500FF);
	else if (start >= 200)
		return (0xDAA520FF);
	else if (start >= 150)
		return (0xFFD700FF);
	else if (start >= 100)
		return (0xDEB887FF);
	else if (start >= 50)
		return (0x778899);
	else
		return (0xBA55D3FF);
}

int	set_color(float y, t_data *data)
{
	float	height;
	float	way;
	int		percent;

	height = (data->mlx->height * 0.4);
	way = y / height;
	percent = (int)(way * 100);
	return (range_up(percent));
}
