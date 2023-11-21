/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayban.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:02:13 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/21 18:06:38 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief This function is used to rotate a victor
 * relative to the origin of the map.
 * receives a vector and an angle in radians
 * modifies x and y of the vector into the new coordinates
 * that the vector will have after rotation.
 * @param victor 
 * @param angle 
 */
void rotate_victor(t_victor *victor, double angle)
{
	double	x;
	double	y;

	x = victor->x;
	y = victor->y;
	victor->x = x * cos(angle * M_PI / 180) - y * sin(angle * M_PI / 180);
	victor->y = x * sin(angle * M_PI / 180) + y * cos(angle * M_PI / 180);
}

void ft_draw_line2(mlx_image_t *img, unsigned int x, int start, unsigned int end, int color, t_data *data, int texx)
{
    if (!img || !img->pixels || !data || !data->sprites[WALL_E] || !data->sprites[WALL_E]->pixels)
        return;

    unsigned int y = start;
    while (y <= end && y < img->height && x < img->width)
    {
        ((uint32_t*)img->pixels)[y * img->width + x] = color;
        y++;
    }

    if (color == 0)
    {
        int texHeight = data->sprites[WALL_E]->height;
        int texWidth = data->sprites[WALL_E]->width;
        y = start;
        while (y <= end && y < img->height && x < img->width)
        {
            int texY = (y - start) * texHeight / (end - start);
            if (texY < 0 || texY >= texHeight || texx < 0 || texx >= texWidth)
            {
                y++;
                continue;
            }

            uint32_t texColor = ((uint32_t*)data->sprites[WALL_E]->pixels)[texY * texWidth + texx];
            if (y >= 0 && y < img->height && x >= 0 && x < img->width)
                ((uint32_t*)img->pixels)[y * img->width + x] = texColor;
            y++;
        }
    }
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
	j = 0;
	img = data->sprites[WALL_E];
	steps = fabs(y2 -y1);//
	step_y_texture = (float)img->height/(float)steps;
	dy = 1;//pantalla es 1 pa la textura
	n = 0;
	while ((int)fabs(y2 - y1))
	{
		//if(x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
		if(x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= data->map.mlx->height)
		{
			row_texture = floor(step_y_texture * n);
			color = ((uint32_t*)img->pixels)[row_texture * img->width + column_texture];
			if(color != 0)
				((uint32_t*)data->map.img3d->pixels)[((int)y1 * data->map.mlx->width + (int)x1)] = color;
		}
		y1 += dy;
		n++;
	}
}


void	ray_render(t_data *data)
{
	double wallx;
	int texx;
		if (data->ray.side == 0)
		{
			data->ray.perpwalldist = (data->ray.sidedistx -  data->ray.deltadistx);
			// data->ray.perpwalldist = (data->ray.mapx - data->player.pos.x + (1 - data->ray.stepx) / 2) / data->ray.raydirx;
			if (data->ray.camerax == 0)
				printf("perpwalldist %f\n", data->ray.perpwalldist);
			wallx = data->player.pos.y + data->ray.perpwalldist * data->ray.raydiry;	
			wallx -= floor((wallx));
			texx = (int)(wallx * (double)data->sprites[WALL_E]->width) % (data->sprites[WALL_E]->width);
		}
		else
		{
			data->ray.perpwalldist = (data->ray.sidedisty -  data->ray.deltadisty);
			// data->ray.perpwalldist = (data->ray.mapy - data->player.pos.y + (1 - data->ray.stepy) / 2) / data->ray.raydiry;
			wallx = data->player.pos.x + data->ray.perpwalldist * data->ray.raydirx;
			wallx -= floor((wallx));
			texx = (int)(wallx * (double)data->sprites[WALL_E]->width) % (data->sprites[WALL_E]->width);
			// texx = (data->sprites[WALL_E]->width) - texx - 1;
			// texx = (int)(wallx * 1000) % (1000);
		}
		// if (fabs(data->ray.perpwalldist) < 0.1)
		// 	data->ray.perpwalldist = 0.1;
		// int texx = (data->ray.x ) % (data->sprites[WALL_E]->width);
		// if (data->ray.side == 0 && data->ray.raydirx > 0)
		// 	texx = (data->sprites[WALL_E]->width) - texx - 1;
		// if (data->ray.side == 1 && data->ray.raydiry < 0)
		// 	texx = (data->sprites[WALL_E]->width) - texx - 1;		
		int lineheight = (int)(((data->map.mlx->height))/2 / data->ray.perpwalldist);
		// if (lineheight > data->map.mlx->height)
		// 	lineheight = data->map.mlx->height;
		// printf("lineheight %d\n", lineheight);
		int drawstart = data->map.mlx->height / 2 - lineheight / 2;
		// printf("drawstart %d\n", drawstart);
		// if (drawstart < 0)
		// 	drawstart = 0;
		int drawend = lineheight / 2 + data->map.mlx->height / 2;
		// if (drawend >= data->map.mlx->height || drawend < 0)
		// 	drawend = data->map.mlx->height -1;
		int color;
		if (data->ray.side == NORTH)
			color = 0xAAAA33CC;
		else
			color = 0xACDDBCAA;
		ft_draw_line(data->map.img3d, data->ray.x, 0, data->ray.x, drawstart -data->player.step_v, data->map.colors[CEILING]);
		// ft_draw_line(data->map.img3d, data->ray.x, drawstart -data->player.step_v, data->ray.x, drawend -data->player.step_v, color);
		// printf("drawstart %d drawend %d\n", drawstart, drawend);
		printf("dist %f\n", data->ray.perpwalldist);
		printf("lineheight %d\n", lineheight);
		drawLineTexture_bonus(data->ray.x, drawstart -data->player.step_v, drawend -data->player.step_v, texx, data, 0);
		// drawLineTexture(data->ray.x, drawstart -data->player.step_v,data->ray.x, drawend -data->player.step_v, texx, data);
		
		// ft_draw_line2(data->map.img3d, data->ray.x, drawstart -data->player.step_v, drawend -data->player.step_v, 0, data, texx);
		//then draw the floor
		ft_draw_line(data->map.img3d, data->ray.x, drawend -data->player.step_v, data->ray.x, data->map.mlx->height, data->map.colors[FLOOR]);
}

void	ray_checkwall(t_data *data)
{
	while (data->ray.hit == 0)
		{
			if (data->ray.sidedistx < data->ray.sidedisty)
			{
				data->ray.sidedistx += data->ray.deltadistx;
				data->ray.mapx += data->ray.stepx;
				data->ray.side = NORTH;
			}
			else
			{
				data->ray.sidedisty += data->ray.deltadisty;                                                                                                                                
				data->ray.mapy += data->ray.stepy;
				data->ray.side = EAST;
			}
			if (data->ray.mapx >= 0 && data->ray.mapx < data->map.width  && data->ray.mapy >= 0 && data->ray.mapy < data->map.height )
			{
				if (data->map.map_aclean[data->ray.mapy][data->ray.mapx] == '1')
					data->ray.hit = 1;
			}
		}
}

void	ray_checkdir(t_data *data)
{
	if (data->ray.raydirx < 0)
	{
		data->ray.stepx = -1;
		data->ray.sidedistx = (data->player.pos.x - data->ray.mapx) * \
		data->ray.deltadistx;
	}
	else
	{
		data->ray.stepx = 1;
		data->ray.sidedistx = (data->ray.mapx + 1.0 - data->player.pos.x) * \
		data->ray.deltadistx;
	}
	if (data->ray.raydiry < 0)
	{
		data->ray.stepy = -1;
		data->ray.sidedisty = (data->player.pos.y - data->ray.mapy) * \
		data->ray.deltadisty;
	}
	else
	{
		data->ray.stepy = 1;
		data->ray.sidedisty = (data->ray.mapy + 1.0 - data->player.pos.y) * \
		data->ray.deltadisty;
	}
}

/**
 * @brief Here we update
 * the ray direction according to the pixel we are drawing
 * and the player position. 
 * 
 * @param data 
 */
void ray_update(t_data *data)
{	
	data->ray.camerax = 2 * data->ray.x / \
	(double)(data->map.width * data->map.ppc) - 1;
	data->ray.raydirx = data->player.vdir.x + \
	data->player.plane.x * data->ray.camerax;
	data->ray.raydiry =data->player.vdir.y + \
	data->player.plane.y * data->ray.camerax;
	data->ray.mapx = (int)data->player.pos.x;
	data->ray.mapy = (int)data->player.pos.y;
	if (data->ray.raydirx == 0)
		data->ray.raydirx = 0.001;
	if (data->ray.raydiry == 0)
		data->ray.raydiry = 0.001;
	data->ray.deltadistx = fabs(1 / data->ray.raydirx);
	// data->ray.deltadistx = sqrt(1 + (data->ray.raydiry * data->ray.raydiry) / (data->ray.raydirx * data->ray.raydirx));
	data->ray.deltadisty = fabs(1 / data->ray.raydiry);
	// data->ray.deltadisty = sqrt(1 + (data->ray.raydirx * data->ray.raydirx) / (data->ray.raydiry * data->ray.raydiry));
	data->ray.hit = 0;
}
//chekcpoint
void ray_bang(t_data *data)
{
	data->ray.x = 0;
	while (data->ray.x < data->map.mlx->width)
	{
		ray_update(data);
		ray_checkdir(data);
		ray_checkwall(data);
		ray_render(data);
		data->ray.x++;
	}	
}
