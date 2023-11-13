/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayban.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:02:13 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/13 19:42:07 by dgarizad         ###   ########.fr       */
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

void ft_draw_line2(mlx_image_t *img, int x, int start, int end, int color, t_data *data, int texx)
{
	int	y;
	
	y = start;
	while (y <= end)
	{
		((uint32_t*)img->pixels)[y * img->width + x] = color;
		y++;
	}
	if (color == 0)
	{
		//HERE WE DRAW THE WALL TEXTURE
		int texHeight = data->sprites[WALL_E]->height;
        int texWidth = data->sprites[WALL_E]->width;
        y = start;
		while (y <= end)
		{
			// Calculate the corresponding position in the texture
			int texY = (y - start) * texHeight / (end - start);

			// Get the color from the texture
			uint32_t texColor = ((uint32_t*)data->sprites[WALL_E]->pixels)[texY * texWidth + texx];

			// Draw the pixel onto the image
			((uint32_t*)img->pixels)[y * img->width + x] = texColor;
			y++;
		}
		
	}
}

void ray_checkdir(t_data *data)
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
	(double)(data->map.width * PPC) - 1;
	data->ray.raydirx = data->player.vdir.x + \
	data->player.plane.x * data->ray.camerax;
	data->ray.raydiry =data->player.vdir.y + \
	data->player.plane.y * data->ray.camerax;
	data->ray.mapx = (int)data->player.pos.x;
	data->ray.mapy = (int)data->player.pos.y;
	if (data->ray.raydirx == 0)
		data->ray.raydirx = 0.0000001;
	if (data->ray.raydiry == 0)
		data->ray.raydiry = 0.0000001;
	data->ray.deltadistx = fabs(1 / data->ray.raydirx);
	data->ray.deltadisty = fabs(1 / data->ray.raydiry);
	data->ray.hit = 0;
}
//chekcpoint
void ray_bang(t_data *data)
{
	data->ray.x = 0;
	while (data->ray.x < data->map.width * PPC)
	{
		ray_update(data);
		ray_checkdir(data);
		while (data->ray.hit == 0)
		{
			if (data->ray.sidedistx < data->ray.sidedisty)
			{
				data->ray.sidedistx += data->ray.deltadistx;
				data->ray.mapx += data->ray.stepx;
				data->ray.side = 0;
			}
			else
			{
				data->ray.sidedisty += data->ray.deltadisty;                                                                                                                                
				data->ray.mapy += data->ray.stepy;
				data->ray.side = 1;
			}
			if (data->ray.mapx >= 0 && data->ray.mapx < data->map.width * PPC && data->ray.mapy >= 0 && data->ray.mapy < data->map.height * PPC)
			{
				if (data->map.map_aclean[data->ray.mapy][data->ray.mapx] == '1')
					data->ray.hit = 1;
			}
		}
		double wallx;
		if (data->ray.side == 0)
		{
			data->ray.perpwalldist = (data->ray.sidedistx -  data->ray.deltadistx);
			wallx = data->player.pos.y + data->ray.perpwalldist * data->ray.raydiry;	
		}
		else
		{
			data->ray.perpwalldist = (data->ray.sidedisty -  data->ray.deltadisty);
			wallx = data->player.pos.x + data->ray.perpwalldist * data->ray.raydirx;
		}
		if (fabs(data->ray.perpwalldist) < 0.001)
			data->ray.perpwalldist = 0.001;
		// int texx = (int)(wallx * (double)data->player.sprites.wall->width);
		int texx = (data->ray.x )%(350);
		if (data->ray.side == 0 && data->ray.raydirx > 0)
			texx = (350) - texx - 1;
		if (data->ray.side == 1 && data->ray.raydiry < 0)
			texx = (350) - texx - 1;	
		int lineheight = (int)(data->map.height * PPC / data->ray.perpwalldist);
		int drawstart = data->map.height * PPC / 2 - lineheight / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + data->map.height * PPC / 2;
		if (drawend >= data->map.height * PPC || drawend < 0)
			drawend = data->map.height * PPC - 1;
		int color;
		if (data->ray.side == 1)
			color = 0xAC00AA55;
		else
			color = 0xACDDBCAA;
		// //first draw the ceiling
		// //DRAW CEILING
		// ft_draw_line2(data->map.img3d, x, 0, drawstart - data->player.step_v, 0x9DA4CFFF, data, texx);
		// //DRAW WALL
		// if (side == 0)
		// 	ft_draw_line2(data->map.img3d, x, drawstart - data->player.step_v, drawend - data->player.step_v, 0, data, texx);
		// else
		// 	ft_draw_line2(data->map.img3d, x, drawstart - data->player.step_v, drawend - data->player.step_v, 0xFFA4CFFF, data, texx);
		// //DRAW FLOOR
		// ft_draw_line2(data->map.img3d, x, drawend - data->player.step_v, data->map.height * PPC -1, 0xCC00BFFF, data, texx);
		ft_draw_line(data->map.img3d, data->ray.x, 0, data->ray.x, drawstart -data->player.step_v, 0x9DA4CFFF);
		ft_draw_line(data->map.img3d, data->ray.x, drawstart -data->player.step_v, data->ray.x, drawend -data->player.step_v, color);
		//then draw the floor
		ft_draw_line(data->map.img3d, data->ray.x, drawend -data->player.step_v, data->ray.x, data->map.height*PPC, 0xCCAABFFF);
		data->ray.x++;
	}	
}
