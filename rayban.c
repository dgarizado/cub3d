/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayban.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:02:13 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/03 19:50:23 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ray_bang(t_data *data)
{
	double planex = 0;
	double planey = 0.66;
	double dirx = 1;
	double diry = 0;
	double posx = data->player.x;
	double posy = data->player.y;
	int x = 0;
	while (x < data->map.width*PPC)
	{
		printf("x = %d\n", x);
		// posx = data->player.x;
		// posy = data->player.y;
		double camerax = 2 * x / (double)(data->map.width*PPC) - 1;
		double raydirx = dirx + planex * camerax;
		double raydiry = diry + planey * camerax;
		printf("raydirx = %f, raydiry = %f\n", raydirx, raydiry);
		int mapx = (int)posx;
		int mapy = (int)posy;
		double sidedistx;
		double sidedisty;
		
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
		int stepx;
		int stepy;
		int hit = 0;
		int side;
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
			
			if (mapx >= 0 && mapx < data->map.width*PPC && mapy >= 0 && mapy < data->map.height*PPC)
			{
				if (data->map.map_aclean[mapy][mapx] == '1')
				{
					printf(BLUE"Wallhit at %d, %d\n"RST, mapx, mapy);
					hit = 1;
				}
			}else 
			 	printf(RED"Invalid map coordinates\n"RST); 
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
			color = 0xACBCAAFF;
		else
			color = 0xACBCBCFF;
		printf("drawstart = %d, drawend = %d\n", drawstart, drawend);
		//first draw the ceiling
		ft_draw_line(data->player.img3d, x, 0, x, drawstart, 0x9DA4CFFF);
		ft_draw_line(data->player.img3d, x, drawstart, x, drawend, color);
		//then draw the floor
		ft_draw_line(data->player.img3d, x, drawend, x, data->map.height*PPC, 0xCCAABFFF);
		x++;
	}	
}