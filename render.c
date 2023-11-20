/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:11:40 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/18 19:22:09 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//THIS WILL BE REPLACED BY VICTORS IN THE FUTURE
void ft_draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	err = dx - dy;
	if (x1 < x2)
		sx = 1;
	else
		sx = -1;
	if (y1 < y2)
		sy = 1;
	else
		sy = -1;
	while (x1 != x2 || y1 != y2)
	{
		if (x1 >= 0 && x1 < (int)img->width && y1 >= 0 && y1 < (int)img->height)
			mlx_put_pixel(img, x1, y1, color);
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void drawLineTexture(double x1, double y1, double x2, double y2, int column_texture, t_data *data)
{
    double dx = x2 - x1;//pantalla
    double dy =  y2 - y1;//pantalla y significa WALL-HEIGHT y esta distancia es la que hay que pintar el sprite proporcionalmente
    double steps;
    mlx_image_t* img;
    int row_texture = 0;//textura
    uint32_t color;
    // if(data->type_wall == 1)
	if (data->ray.side == 0)
        img = data->sprites[WALL_N];
	if (data->ray.side == 1)
		img = data->sprites[WALL_E];	
    // else if(data->type_wall == 8)
    //     img = data->broken;
    // else if(data->type_wall == 7)
    //     img = data->zombie;
	// double texture_scale = data->ray.perpwalldist / 2;
	// int texture_height = (int)(texture_scale * img->height);
	// int texture_start = (img->height - texture_height) / 2;
	// int texture_end = texture_start + texture_height;
	int lineheight = (int)(data->map.mlx->height / data->ray.perpwalldist);
		if (lineheight > data->map.mlx->height)
			lineheight = data->map.mlx->height;
    if ((abs)((int)dx) >= (abs)((int)dy))
        steps = (fabs)(dx);//pantalla
    else
        steps = (fabs)(dy);//pantalla esta saldra siempre pa la textura
    // float step_y_texture = (float)img->height/(float)steps;
	// int texture_middle = img->height / 2;
	double textStep = 1.0 * img->height / lineheight;
    // double texpos = (y1 - data->map.mlx->height / 2 + lineheight / 2) * textStep;
	// double textStep = 1.0 * (img->height - texture_middle) / (data->map.mlx->height / 2);
	dx = dx / steps;//pantalla
    dy = dy / steps;//pantalla es 1 pa la textura
    int n = 0;
    while ((int)fabs(x2 - x1) || (int)fabs(y2 - y1))
    {
        row_texture = floor(textStep * n);
        if(x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
        {
            color = ((uint32_t*)img->pixels)[row_texture * img->width + column_texture];
            if(color != 0)
                ((uint32_t*)data->map.img3d->pixels)[((int)y1 * data->map.img3d->width + (int)x1)] = color;
        }
        y1 += dy;
        n++;
    }
}