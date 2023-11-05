/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayban.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:02:13 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/05 15:34:39 by dgarizad         ###   ########.fr       */
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

void ray_bang(t_data *data)
{
	double planex = data->player.plane.x;
	double planey = data->player.plane.y;
	double dirx = data->player.vdir.x;
	double diry = data->player.vdir.y;
	double posx = data->player.x;
	double posy = data->player.y;
	double camerax;
	double raydirx;
	double raydiry;
	int mapx;
	int mapy;
	double sidedistx;
	double sidedisty;
	int stepx;
	int stepy;
	int hit;
	int side;
	int x = 0;
	while (x < data->map.width*PPC)
	{
		printf("x = %d\n", x);
		// posx = data->player.x;
		// posy = data->player.y;
		camerax = 2 * x / (double)(data->map.width*PPC) - 1;
		raydirx = dirx + planex * camerax;
		raydiry = diry + planey * camerax;
		printf("raydirx = %f, raydiry = %f\n", raydirx, raydiry);
		mapx = (int)posx;
		mapy = (int)posy;
		if (raydirx == 0)
		{
			printf("raydirx = 0\n");
			// getchar();
			raydirx = 0.0000001;
		}
		double deltadistx = fabs(1 / raydirx);
		if (raydiry == 0)
		{
			printf("raydiry = 0\n");
			// getchar();
			raydiry = 0.0000001;
		}
		double deltadisty = fabs(1 / raydiry);
		printf("deltadistx = %f, deltadisty = %f\n", deltadistx, deltadisty);
		double perpwalldist;
		hit = 0;
		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (posx - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - posx) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (posy - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - posy) * deltadisty;
		}
		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			printf("mapx = %d, mapy = %d\n", mapx, mapy);
			
			// if (mapx >= 0 && mapx < data->map.width*PPC && mapy >= 0 && mapy < data->map.height*PPC)
			// {
				if (data->map.map_aclean[mapy][mapx] == '1')
				{
					printf(BLUE"Wallhit at %d, %d\n"RST, mapx, mapy);
					hit = 1;
				}
			// }else 
			//  	printf(RED"Invalid map coordinates\n"RST); 
		}
		if (side == 0)
		{

			perpwalldist = (sidedistx -  deltadistx);
			
		}
		else
		{
			perpwalldist = (sidedisty -  deltadisty);
		}
		
		int lineheight = (int)(data->map.height*PPC / perpwalldist);
		printf("raydirx = %f, raydiry = %f\n", raydirx, raydiry);
		printf("lineheight = %d\n", lineheight);
		printf("perpwalldist = %f\n", perpwalldist);
		printf("data->map.height*PPC = %d\n", data->map.height*PPC);
		int drawstart = -lineheight / 2 + data->map.height*PPC / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + data->map.height*PPC / 2;
		if (drawend >= data->map.height*PPC || drawend < 0)
			drawend = data->map.height*PPC - 1;
		int color;
		if (side == 1)
			color = 0xAC00AA55;
		else
			color = 0xACDDBCAA;
		printf("drawstart = %d, drawend = %d\n", drawstart, drawend);
		//position
		printf("posx = %f, posy = %f\n", posx, posy);
		//first draw the ceiling
		ft_draw_line(data->player.img3d, x, 0, x, drawstart -data->player.vertical, 0x9DA4CFFF);
		ft_draw_line(data->player.img3d, x, drawstart -data->player.vertical, x, drawend -data->player.vertical, color);
		//then draw the floor
		ft_draw_line(data->player.img3d, x, drawend -data->player.vertical, x, data->map.height*PPC, 0xCCAABFFF);
		x++;
	}	
}
