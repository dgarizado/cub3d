/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:36:01 by vcereced          #+#    #+#             */
/*   Updated: 2024/01/14 18:02:22 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_transition(int *n, t_data *data)
{
	(*n) += 1;
	if (*n == 155)
	{
		data->img[MAP_INTRO]->enabled = 0;
		data->img[TITLE_INTRO]->enabled = 0;
		data->phase = 1;
		data->sprites[PISTOL]->instances[0].enabled = true;
	}
	else if ((*n) == 150)
		ft_memset(data->img[TITLE_INTRO]->pixels, 0, data->mlx->width * 0.9 \
	* data->mlx->height * 0.4 * sizeof(int32_t));
	else if ((*n) > 30 && (*n) < 120)
		ft_memset(data->img[MAP_INTRO]->pixels, 255 - ((*n) * 2), \
	data->mlx->width * data->mlx->height * sizeof(int32_t));
	else if ((*n) < 30)
	{
		data->title.boom += 0.2;
		ft_memset(data->img[MAP_INTRO]->pixels, 0, data->mlx->width \
		* data->mlx->height * sizeof(int32_t));
		draw_title(data);
		draw_title_map(data);
	}
}

void	ft_game_loop(void *d)
{
	t_data	*data;

	data = (t_data *)d;
	if (mlx_is_key_down(data->mlx, 256))
		mlx_close_window(data->mlx);
	ft_memset(data->img[MINIMAP_GAME]->pixels, 0, (int)(data->mlx->width * 0.3) \
	*(int)(data->mlx->height * 0.3) * sizeof(int));
	ft_move_players(data);
	ft_draw_minimap(data);
	raycast_game(data);
	mouse(data);
	ft_kill(data);
}

void	ft_intro_loop(t_data	*data)
{
	static int	n;

	data->title.color_up += 15 ;
	if (data->title.color_up >= ((data->mlx->height * 0.4) * 3))
		data->title.color_up = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ENTER))
		data->title.flag = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (data->title.flag == 0)
	{
		draw_title_map(data);
		draw_title(data);
	}
	if (data->title.flag == 1)
		ft_transition(&n, data);
}

void	ft_loop(void *d)
{
	t_data	*data;

	data = (t_data *)d;
	if (data->phase == 0)
		ft_intro_loop(data);
	else if (data->phase == 1)
		ft_game_loop(data);
}
