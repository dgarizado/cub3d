/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_charles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:47:26 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/05 14:25:47 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double d2r(double angle)
{
	printf("degrees to rad\n");
	printf("angle = %f\n", angle);
	
	return (angle * 3.14159265 / 180);
}

void	ray_charles(t_data *data)
{
	int screenw;
	int screenh;
	double increment;
	double ray_angle;
	int i;
	double ray_x;
	double ray_y;
	double ray_xstep;
	double ray_ystep;
	double ray_dist;
	int wallhit;
	int wallheight;

	screenw = data->map.width*40;
	screenh = data->map.height*40;
	increment = (double)FOV / (double)screenw;
	ray_angle = data->player.angle - (FOV / 2);
	i = 0;
	printf("Player angle = %f\n", data->player.angle);
	printf("increment = %f\n", increment);
	printf("screenw = %d\n", screenw/2);
	printf("ray_angle = %f\n", ray_angle);
	printf("ray_angle in rads = %f\n", d2r(ray_angle));
	while (i++ < screenw)
	{
		printf("i = %d\n", i);
		ray_x = data->player.x;
		ray_y = data->player.y;
		if (ray_angle < 0)
			ray_angle += 360;
		if (ray_angle > 360)
			ray_angle -= 360;
		ray_xstep = cos(d2r(ray_angle))/16;
		ray_ystep = sin(d2r(ray_angle))/16;
		printf("ray_xstep = %f\n", ray_xstep);
		printf("ray_ystep = %f\n", ray_ystep);
		wallhit = 0;
		while (wallhit == 0)
		{
			printf("ray_x = %f\n", ray_x);
			printf("ray_y = %f\n", ray_y);
			ray_x += ray_xstep;
			ray_y += ray_ystep;
			printf("map_aclean = %c\n", data->map.map_aclean[(int)ray_y][(int)ray_x]);
			printf("i = %d\n", i);
			if (data->map.map_aclean[(int)ray_y][(int)ray_x] == '1')
			{
				wallhit = 1;
				printf(BLUE"wallhit at %d, %d\n"RST, (int)ray_x, (int)ray_y);
				printf("map_aclean = %c\n", data->map.map_aclean[(int)ray_y][(int)ray_x]);
				printf("i = %d\n", i);
			}
		}
		ray_dist = sqrt(pow(ray_x - data->player.x, 2) + pow(ray_y - data->player.y, 2));
		// ray_dist = ray_dist * cos(d2r(ray_angle - data->player.angle));
		wallheight = (int)((screenh/2) / ray_dist);
		ft_draw_line(data->player.img3d, (int)(i), (int)(screenh/2 - wallheight), (int)(i), (int)(screenh/2 + wallheight) -10, 0xFF00FFFF);
		ft_draw_line(data->player.img3d, i, 0, i, screenh/2 - wallheight, 0xACBCBCFF);
		ft_draw_line(data->player.img3d, i, screenh/2 + wallheight, i, screenh, 0x9DA4CFFF);
		ray_angle += increment;
		printf("ray_angle = %f\n", ray_angle);
	}	
	// i = 0;
	// while (i < data->map.width*PPC/2)
	// {
	// 	mlx_put_pixel(data->player.img3d, i, 0, 0xACFFFF);
	// 	mlx_put_pixel(data->player.img3d, i, data->map.height*PPC/2 - 1, 0xACFFFF);
	// 	i++;
	// }
	// i = 0;
	// while (i < data->map.height*PPC/2)
	// {
	// 	mlx_put_pixel(data->player.img3d, 0, i, 0xACFFFF);
	// 	mlx_put_pixel(data->player.img3d, data->map.width*PPC/2 - 1, i, 0xACFFFF);
	// 	i++;
	// }
}
