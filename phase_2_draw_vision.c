/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase_2_draw_vision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:54:24 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/05 18:50:22 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//mlx_draw_texture(data->game, data->linktexture, (3 * (data->map.atr.scale_width_mini_map / 10)), (3 * (data->map.atr.scale_height_mini_map/10)));

void	ft_vision(double angle, t_data *data)
{
	int cont;
	double x2 = (3 * (data->map.atr.scale_width_mini_map / 10));
	double y2 = (3 * (data->map.atr.scale_height_mini_map/10));

	
	double rayCos =  cos(ft_degre_to_radian(angle));
    double raySin = sin(ft_degre_to_radian(angle));
	
	//char wall = '0';
	//cont = 0;
	//while(wall != '1' && cont < 2) {
	//	x2 += rayCos;
	//	y2 += raySin;
	//	cont++;
	//	wall = data->map.map[(((int)(fabs)(y2)) * data->map.largo) + ((int)(fabs)(x2))];
	//}
	
	cont = 0;
	while(cont < 50) 
	{
      	x2 += rayCos;
        y2 += raySin;
		cont++;
	}
	double x1 =  3*(data->map.atr.scale_width_mini_map / 10);
	double y1 =  3*(data->map.atr.scale_height_mini_map / 10);

	drawLine(x1, y1, x2, y2, 0xAC00AAFF, data->game, data);
	//drawLine(data->player.x, data->player.y, x2,  y2, 0xAC00AAFF, data->game);
}

void draw_angle(t_data *data)
{
	int cont;
	double x2 = (3 * (data->map.atr.scale_width_mini_map / 10));
	double y2 = (3 * (data->map.atr.scale_height_mini_map/10));
	double angle_start = data->player.angle - data->player.half_fov;
	double angle_end =  data->player.angle + data->player.half_fov;//PRUEBA
	printf("start %f end %f", angle_start, angle_end);
	//getchar();

	ft_vision(angle_start, data);
	ft_vision(data->player.angle, data);
	ft_vision(angle_end, data);
	
}

void	draw_vision(t_data *data)
{
	draw_angle(data);
}