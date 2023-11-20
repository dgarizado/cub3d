/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:10:37 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/20 13:21:12 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t* choose_image(int j, t_data *data)
{
	mlx_image_t* img;
	
	if (j == -1)//OJO ZOMIBEEEEEEE
		img = data->zombie;
	else if(data->cast.bonus.type_wall_bonus[j] == 9 || data->cast.bonus.type_wall_bonus[j] == 1)//OJO IGUAL PUERTA Y MURO
		img = data->wall_img;
	else if(data->cast.bonus.type_wall_bonus[j] == 8)
		img = data->broken;
	else if(data->cast.bonus.type_wall_bonus[j] == 6)
		img = data->grass;
	else if(data->cast.bonus.type_wall_bonus[j] == 5)
		img = data->aura;
	return (img);
}

void drawLineTexture_bonus(double x1, double y1, double y2, int column_texture, t_data *data, int j)
{
	double dy;//pantalla y significa WALL-HEIGHT y esta distancia es la que hay que pintar el sprite proporcionalmente
	double steps;
	mlx_image_t* img;
	int row_texture;//textura
	uint32_t color;
	int n;
	float step_y_texture;
	
	img = choose_image(j, data);
	steps = fabs(y2 -y1);//
	step_y_texture = (float)img->height/(float)steps;
	dy = 1;//pantalla es 1 pa la textura
	n = 0;
	while ((int)fabs(y2 - y1))
	{
		//if(x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
		if(x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= data->mlx->height)
		{
			row_texture = floor(step_y_texture * n);
			color = ((uint32_t*)img->pixels)[row_texture * img->width + column_texture];
			if(color != 0)
				((uint32_t*)data->game->pixels)[((int)y1 * data->game->width + (int)x1)] = color;
		}
		y1 += dy;
		n++;
	}
}
