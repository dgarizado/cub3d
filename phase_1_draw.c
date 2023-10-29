/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase_1_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:29:45 by vcereced          #+#    #+#             */
/*   Updated: 2023/10/29 12:29:28 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	range_down(float start)
{
	if (start <= -90)
		return (0xC71585);
	else if (start <= -75)
		return (0xFF00FF);
	else if (start <= -60)
		return (0xDA70D6);
	else if (start <= -45)
		return (0x7B68EE);
	else if (start <= -30)
		return (0x1E90FF);
	else if (start <= -15)
		return (0x6495ED);
	else
		return (0x00BFFF);
}

static int	range_up(int start)
{
	/*if (start >= 95)
		return (0x7B1FA2FF);
	else if (start >= 85)
		return (0xBA55D3FF);
	else if (start >= 70)
		return (0xFFA500FF);
	else if (start >= 55)
		return (0xDAA520FF);
	else if (start >= 35)
		return (0xFFD700FF);
	else if (start >= 25)
		return (0xDEB887FF);
	else if (start >= 15)
		return (0xDCDCDCFF);
	else
		return (0x778899);*/

	if (start >= 350)
		return (0x778899);
	else if (start >= 300)
		return (0xBA55D3FF);
	else if (start >= 250)
		return (0xFFA500FF);
	else if (start >= 200)
		return (0xDAA520FF);
	else if (start >= 150)
		return (0xFFD700FF);
	else if (start >= 100)
		return (0xDEB887FF);
	else if (start >= 50)
		return (0x778899);
	else
		return (0xBA55D3FF);
	

		
}

int	set_color(float y)
{
	float		height;
	float	way;
	int 	percent;

	
	
	height = (HEIGHT_IMG_TITLE);
	way = y / height;
	percent = (int)(way*100);
	//printf("height %f\n", height);
	//printf("WAY %f\n",way);
//	printf("%f de color %f\n",y,  HEIGHT_IMG_TITLE);
	//printf("percent %d\n", percent);
	
	if (percent >= 0)
		return (range_up(percent));
	else
		return (range_down(percent));
}

static void	ft_draw_sq(mlx_image_t* img2, t_data * data, int x1, int y1)
{
	int x;
	int y;
	int last_x;
	int last_y;
	last_x = x1 + ((fabs)((WIDTH_IMG_TITLE_MAP) / data->map.width));
	last_y = y1 + ((fabs)(HEIGTH_IMG_TITLE_MAP) / data->map.height);

	y =y1;
	while(y <= last_y)
	{
		x =x1;
		
		while(x <= last_x)
		{
			mlx_put_pixel(img2, x, y, 0xDAA520FF);
			x++;
		}
		
		y++;
	}
}

static void draw_square(t_data * data, mlx_image_t* img2, int row, int column)
{
	int x1;
	int y1;

	x1 = column * ((fabs)(WIDTH_IMG_TITLE_MAP) / data->map.width);
	y1 = row * ((fabs)((HEIGTH_IMG_TITLE_MAP) / data->map.height));
	ft_draw_sq(img2, data, x1, y1);
}

void	draw_title_map(t_data *data, mlx_image_t* img2)
{
	int row;
	int column;

	row = 0;
	while(data->map.map_aclean[row])
	{
		column = 0;
		while(data->map.map_aclean[row][column])
		{
			if(data->map.map_aclean[row][column] == '1')
				draw_square(data, img2, row, column);
			column++;
		}
	
		row++;
	}
}
