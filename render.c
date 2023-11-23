/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:11:40 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/23 22:55:03 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t apply_shading(uint32_t color, double shading_factor)
{
    uint8_t r, g, b, a;

    // Extract the RGBA components from the color
    r = (color >> 24) & 0xFF;
    g = (color >> 16) & 0xFF;
    b = (color >> 8) & 0xFF;
    a = color & 0xFF;

    // Apply the shading factor to each component
    r = (uint8_t)(r * shading_factor);
    g = (uint8_t)(g * shading_factor);
    b = (uint8_t)(b * shading_factor);
    a = (uint8_t)(a * shading_factor);

    // Combine the components back into a single color
    return (r << 24) | (g << 16) | (b << 8) | a;
}



void	drawline(t_data *data, int flag)
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
		if (data->ray.x >= 0 && data->ray.x <= WIDTH && \
		drawstart >= 0 && drawstart <= HEIGHT)
			mlx_put_pixel(data->map.img3d, (int)data->ray.x, \
			(int)drawstart, data->map.colors[flag]);
		drawstart += dy;
	}
}

/**
 * @brief For norminette issues, this function is used to draw the texture
 * when the distance is less than 1. The return value is used to calculate
 * the step_y_texture in the ray_render function.
 * @param data 
 * @param step_y_texture 
 * @param column_texture 
 * @param img 
 * @return float 
 */
float	draw_awx(t_data *data, float step_y_texture, \
int column_texture, mlx_image_t *img)
{
	int	y;
	int	row_texture;
	int	n;

	n = 0;
	if (data->ray.perpwalldist < 1)
	{
		step_y_texture = 1.0 * img->height / fabs(data->ray.drawend \
		- data->ray.drawstart) * data->ray.perpwalldist;
		y = data->ray.drawstart;
		while (y < data->ray.drawend)
		{
			row_texture = (int)((y - data->map.mlx->height / 2) * \
			step_y_texture + img->height / 2);
			((uint32_t *)data->map.img3d->pixels)[((int)data->ray.drawstart * \
			data->map.mlx->width + (int)data->ray.x)] = ((uint32_t *) \
			img->pixels)[row_texture * img->width + column_texture];
			y++;
			data->ray.drawstart++;
			n++;
		}
	}
	return ((float)img->height / fabs(data->ray.drawend - data->ray.drawstart));
}

void	drawlinetexture(double x1, int column_texture, t_data *data)
{
	mlx_image_t		*img;
	int				row_texture;
	int				n;
	float			step_y_texture;

	double shading_factor;
	shading_factor = 1.0 - data->ray.perpwalldist / 25;
	if (shading_factor < 0.2)
		shading_factor = 0.2;
	img = data->sprites[data->ray.side];
	step_y_texture = draw_awx(data, 0, column_texture, img);
	n = 0;
	if (data->ray.perpwalldist >= 1)
	{
		while ((int)fabs(data->ray.drawend - data->ray.drawstart))
		{
			if (x1 >= 0 && x1 <= WIDTH && data->ray.drawstart >= 0 \
			&& data->ray.drawstart <= data->map.mlx->height)
			{
				row_texture = floor(step_y_texture * n);
				((uint32_t *)data->map.img3d->pixels)[((int)data->ray.drawstart \
				* data->map.mlx->width + (int)x1)] = apply_shading(((uint32_t *)img->pixels) \
				[row_texture * img->width + column_texture],shading_factor);
			}
			data->ray.drawstart++;
			n++;
		}
	}
}

void	render_aux(t_data *data, int texx)
{
	
	
	data->ray.lineheight = (int)(((data->map.mlx->height)) \
	/ data->ray.perpwalldist);
	if (data->ray.lineheight > data->map.mlx->height)
		data->ray.lineheight = data->map.mlx->height;
	data->ray.drawstart = data->map.mlx->height / 2 - data->ray.lineheight / 2;
	if (data->ray.drawstart < 0 || data->ray.drawstart >= data->map.mlx->height)
		data->ray.drawstart = 0;
	data->ray.drawend = data->ray.lineheight / 2 + data->map.mlx->height / 2;
	if (data->ray.drawend >= data->map.mlx->height || data->ray.drawend < 0)
		data->ray.drawend = data->map.mlx->height;
	drawline(data, CEILING);
	drawlinetexture(data->ray.x, texx, data);
	drawline(data, FLOOR);
}

void	ray_render(t_data *data)
{
	double	wallx;
	int		texx;

	if (data->ray.side == TEX_E || data->ray.side == TEX_W)
	{
		data->ray.perpwalldist = (data->ray.sidedistx - data->ray.deltadistx);
		wallx = data->player.pos.y + data->ray.perpwalldist * data->ray.raydiry;
		wallx -= floor((wallx));
		texx = (int)(wallx * (double)data->sprites[data->ray.side]->width) % \
		(data->sprites[data->ray.side]->width);
		if (data->ray.side == TEX_W)
			texx = data->sprites[data->ray.side]->width - texx - 1;
	}
	else
	{
		data->ray.perpwalldist = (data->ray.sidedisty - data->ray.deltadisty);
		wallx = data->player.pos.x + data->ray.perpwalldist * data->ray.raydirx;
		wallx -= floor((wallx));
		texx = (int)(wallx * (double)data->sprites[data->ray.side]->width) % \
		(data->sprites[data->ray.side]->width);
		if (data->ray.side == TEX_S)
			texx = data->sprites[data->ray.side]->width - texx - 1;
	}
	render_aux(data, texx);
}
