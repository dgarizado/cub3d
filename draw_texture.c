/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:10:37 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/24 14:18:49 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t* choose_orientation(int j, t_data *data)
{
	if (data->cast.bonus.flag_bonus[j] == 'x' && data->cast.bonus.cell_step_bonus[j] == -1)
		return (data->sprites[WALL_W]);
	else if (data->cast.bonus.flag_bonus[j] == 'x' && data->cast.bonus.cell_step_bonus[j] == 1)
		return (data->sprites[WALL_E]);
	else if (data->cast.bonus.flag_bonus[j] == 'y' && data->cast.bonus.cell_step_bonus[j] == -1)
		return (data->sprites[WALL_N]);
	else if (data->cast.bonus.flag_bonus[j] == 'y' && data->cast.bonus.cell_step_bonus[j] == 1)
		return (data->sprites[WALL_S]);
	return (NULL);
}

mlx_image_t* choose_image(int j, t_data *data)
{
	mlx_image_t* img;
	int n = data->cast.bonus.n;
	
	if (n == -1)//OJO ZOMIBEEEEEEE
		img = data->sprites[ENEMY];
	else if(data->cast.bonus.type_wall_bonus[n] == '1')
	{
		img = choose_orientation(n, data);
	}
	else if(data->cast.bonus.type_wall_bonus[n] == '9')//OJO IGUAL PUERTA Y MURO
	img = data->sprites[WALL_TO_BROKE];
	else if(data->cast.bonus.type_wall_bonus[n] == 'B')
	img = data->sprites[BROKEN];
	else if(data->cast.bonus.type_wall_bonus[n] == 'G')
		img = data->sprites[GRASS];
	else if(data->cast.bonus.type_wall_bonus[n] == '5')
		img = data->sprites[AURA];
	return (img);
}
void drawlinetexture_bonus(double x1, double y1, double y2, t_data *data)
{
	double steps;
	mlx_image_t* img;
	int row_texture;
	uint32_t color;
	int n;
	float step_y_texture;
	
	img = choose_image(n, data);
	steps = fabs(y2 -y1);
	step_y_texture = (float)img->height/(float)steps;
	
	n = 0;
	while ((int)fabs(y2 - y1))
	{
		if(x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
		{
			row_texture = floor(step_y_texture * n);
			color = ((uint32_t*)img->pixels)[(row_texture * img->width) + (data->column_texture)];
			if(color != 0)
				((uint32_t*)data->img[GAME]->pixels)[((int)y1 * data->img[GAME]->width + (int)x1)] = color;
		}
		y1++;
		n++;
	}
}
