/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:02:39 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/10 12:18:45 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_parse_map(char **arr, t_data *data)
{
	int len;
	int width;
	char *buffer;
	int i;
	
	data->map.ancho = ft_arrlen(arr) - 6;
	data->map.largo =  ft_strlen(arr[6]);

	buffer = (char *)malloc(data->map.largo * data->map.ancho + 1);
	buffer[0] = '\0';
	i = 6;
	while(i < data->map.ancho + 6)//hardcoded!!!!!!
		ft_strlcat(buffer, arr[i++], data->map.largo * data->map.ancho);
	data->map.map = buffer;
	printf("%s", data->map.map);
}

void set_x_y_player_N(t_data *data)
{
	int row;
	int column;
	
	row = 0;
	while(row < data->map.ancho)
	{
		column = 0;
		while(column < data->map.largo)
		{
			//if(data->map.map[(row * data->map.largo) + column] == 49)
			//	draw_square(data, row, column, 0xBA55D3FF);
			if(data->map.map[(row * data->map.largo) + column] == 'N')
			{
				data->player.x = column;
				data->player.y = row;
			}
			column++;
		}
		row++;
	}
}

void	set_atr_game(t_data *data)
{
	data->map.atr.screen_width = WIDTH;
	data->map.atr.screen_height = HEIGHT;
	data->map.atr.screen_half_width = WIDTH/2;
	data->map.atr.screen_half_height = HEIGHT/2;
	data->map.atr.scale_width_mini_map = (WIDTH * 0.2);
	data->map.atr.scale_height_mini_map = (HEIGHT * 0.2);
	data->map.atr.screen_up = 0;
	
	data->map.atr.render_delay = 1000000;
	data->map.atr.precision	= 64;
	data->player.fov = 60;
	data->player.half_fov = data->player.fov / 2;
	//data->player.x = 2;
	//data->player.y = 4;
	data->player.angle = 300;
	data->map.atr.r_c_increment_angle = data->player.fov / data->map.atr.screen_width;
	
	set_x_y_player_N(data);
}





void	ft_phase_2(t_data *data, mlx_t* mlx)
{
	data->linktexture = mlx_load_png("./texture_link/link.png");
	data->mlx = mlx;
	ft_parse_map(data->map.map_a, data);
	set_atr_game(data);
	data->game = mlx_new_image(mlx, data->map.atr.screen_width * 0.3 , data->map.atr.screen_height * 0.2);
//	mlx_loop_hook(mlx, draww, data);SAltamos
	
}