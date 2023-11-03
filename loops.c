/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:34:20 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/03 19:41:33 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_move(t_data *data, int mode)
{
	if (mode == 1)
	{
		if(data->player.y > 0 && data->map.map[(((data->player.y)-1) * data->map.largo) + data->player.x] != '1')
			data->player.y -=1;
	}
	else if (mode == 2)
	{
		if(data->player.y < data->map.ancho && data->map.map[((((data->player.y) + 1) * data->map.largo)) + data->player.x] != '1')
		data->player.y +=1;
	}
	else if (mode == 3)
	{
		if(data->player.x > 0  && data->map.map[((data->player.y * data->map.largo)) + (data->player.x - 1)] != '1')
		data->player.x -=1;
	}
	else if (mode == 4)
	{
		if(data->player.x < data->map.largo  && data->map.map[((data->player.y * data->map.largo)) + (data->player.x + 1)] != '1')
		data->player.x +=1;
	}
}

void hk2(void *d)
{

	t_data *data = (t_data *)d; 
	
	if (data->flag == 1)
	{
		usleep(100000);
		if (mlx_is_key_down(data->mlx, 256))
			mlx_close_window(data->mlx);
		else if (mlx_is_key_down(data->mlx, MLX_KEY_W))
			check_move(data, 1);
		else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
			check_move(data, 2);
		else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
			check_move(data, 3);
		else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
			check_move(data, 4);
		printf("x= %d, y= %d\n", data->player.x, data->player.y);
		ft_memset(data->game->pixels, 0 , (data->map.atr.screen_width * 0.3) * (data->map.atr.screen_height * 0.2)* sizeof(int32_t));
		ft_game_little_map(data);
		ft_game_play(data);
	}
}