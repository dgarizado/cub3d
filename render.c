/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:11:40 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/23 17:22:18 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	drawline(t_data *data , int flag)
{
	double	dy;
	double	steps;
	double	drawstart;
	double	drawend;

	if (flag == CEILING)
	{
		drawstart = 0;
		drawend = data->ray.drawstart - data->player.step_v;
	}
	else
	{
		drawstart = data->ray.drawend - data->player.step_v;
		drawend = data->map.mlx->height;
	}
	steps = fabs(drawend - drawstart);
	dy = (drawend - drawstart) / steps;
	while ((int)fabs(drawend - drawstart))
	{
		if(data->ray.x >= 0 &&data->ray.x <= WIDTH && drawstart >= 0 && drawstart <= HEIGHT)
			mlx_put_pixel(data->map.img3d, (int)data->ray.x, (int)drawstart, data->map.colors[flag]);
		drawstart += dy;
	}
}
//CP
// void	get_texture(t_data *data)
// {
	
// }

void	drawlinetexture(double x1, double drawstart, double drawend, int column_texture, t_data *data, int j)
{
	double steps;
	mlx_image_t* img;
	int row_texture;//textura
	uint32_t color;
	int n;
	float step_y_texture;

	j = 0;
	img = data->sprites[WALL_E];
	steps = fabs(drawend - drawstart);
	step_y_texture = (float)img->height/(float)steps;
	n = 0;
	if (data->ray.perpwalldist < 1)
	{
		step_y_texture = 1.0 * img->height / steps * data->ray.perpwalldist;
		int y = drawstart;
		while (y < drawend)
		{
			row_texture = (int)((y - data->map.mlx->height / 2) * step_y_texture + img->height / 2);
			// while (row_texture < 0) {
			// 	row_texture += img->height;
			// }
			// while (row_texture >= (int)img->height) {
			// 	row_texture -= img->height;
			// }
			color = ((uint32_t*)img->pixels)[row_texture * img->width + column_texture];
			if(color != 0)
				((uint32_t*)data->map.img3d->pixels)[((int)drawstart * data->map.mlx->width + (int)x1)] = color;

			y++;
			drawstart++;
			n++;
		}
	}else {
	while ((int)fabs(drawend - drawstart))
	{
		if(x1 >= 0 && x1 <= WIDTH && drawstart >= 0 && drawstart <= data->map.mlx->height)
		{
			row_texture = floor(step_y_texture * n);
			color = ((uint32_t*)img->pixels)[row_texture * img->width + column_texture];
			if(color != 0)
				((uint32_t*)data->map.img3d->pixels)[((int)drawstart * data->map.mlx->width + (int)x1)] = color;
		}
		drawstart++;
		n++;
	}}
}

void	render_aux(t_data *data, int texx)
{
	data->ray.lineheight = (int)(((data->map.mlx->height)) / data->ray.perpwalldist);
	if (data->ray.lineheight > data->map.mlx->height)
		data->ray.lineheight = data->map.mlx->height;
	data->ray.drawstart = data->map.mlx->height / 2 - data->ray.lineheight / 2;
	if (data->ray.drawstart < 0 || data->ray.drawstart >= data->map.mlx->height)
		data->ray.drawstart = 0;
	data->ray.drawend = data->ray.lineheight / 2 + data->map.mlx->height / 2;
	if (data->ray.drawend >= data->map.mlx->height || data->ray.drawend < 0)
		data->ray.drawend = data->map.mlx->height;
	drawline(data, CEILING);
	drawlinetexture(data->ray.x, data->ray.drawstart - data->player.step_v, \
	data->ray.drawend - data->player.step_v, texx, data, 0);
	drawline(data, FLOOR);
}

// void	render_aux(t_data *data, int texx)
// {
// 	data->ray.lineheight = (int)(((data->map.mlx->height)) / data->ray.perpwalldist);
// 	if (data->ray.lineheight > data->map.mlx->height)
// 		data->ray.lineheight = data->map.mlx->height;
// 	data->ray.drawstart = data->map.mlx->height / 2 - data->ray.lineheight / 2;
// 	if (data->ray.drawstart < 0 || data->ray.drawstart >= data->map.mlx->height)
// 		data->ray.drawstart = 0;
// 	data->ray.drawend = data->ray.lineheight / 2 + data->map.mlx->height / 2;
// 	if (data->ray.drawend >= data->map.mlx->height || data->ray.drawend < 0)
// 		data->ray.drawend = data->map.mlx->height;
// 	drawline(data, data->ray.x, 0, data->ray.drawstart - data->player.step_v, \
// 	data->map.colors[CEILING], data->map.img3d);
// 	drawlinetexture(data->ray.x, data->ray.drawstart - data->player.step_v, \
// 	data->ray.drawend - data->player.step_v, texx, data, 0);
// 	drawline(data, data->ray.x, data->ray.drawend -data->player.step_v, data->map.mlx->height, \
// 	data->map.colors[FLOOR], data->map.img3d);
// }

void	ray_render(t_data *data)
{
	double	wallx;
	int		texx;

	if (data->ray.side == 0)
	{
		data->ray.perpwalldist = (data->ray.sidedistx -  data->ray.deltadistx);
		wallx = data->player.pos.y + data->ray.perpwalldist * data->ray.raydiry;	
		wallx -= floor((wallx));
		texx = (int)(wallx * (double)data->sprites[WALL_E]->width) % (data->sprites[WALL_E]->width);
	}
	else
	{
		data->ray.perpwalldist = (data->ray.sidedisty -  data->ray.deltadisty);
		wallx = data->player.pos.x + data->ray.perpwalldist * data->ray.raydirx;
		wallx -= floor((wallx));
		texx = (int)(wallx * (double)data->sprites[WALL_E]->width) % (data->sprites[WALL_E]->width);
	}
	render_aux(data, texx);
}


