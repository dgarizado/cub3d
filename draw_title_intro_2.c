/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_title_intro_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 00:19:52 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/17 01:38:31 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int 	percent;

	height = (HEIGHT_IMG_TITLE);
	way = y / height;
	percent = (int)(way*100);
	return (range_up(percent));
}