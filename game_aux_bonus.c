/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_aux_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:07:18 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/23 20:39:26 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void ft_fix_images(t_data *data)
// {
// 	mlx_resize_image(data->map.img3d, data->map.mlx->width, \
// 	data->map.mlx->height);
// 	data->map.ppc = data->map.mlx->width / data->map.width;
// 	data->sprites[PISTOL]->instances[0].x = data->map.mlx->width / 2 - \
// 	data->sprites[PISTOL]->width / 2;
// 	data->sprites[PISTOL]->instances[0].y = data->map.mlx->height - \
// 	data->sprites[PISTOL]->height;
// 	data->sprites[PISTOL_BANG]->instances[0].x = data->map.mlx->width / 2 - \
// 	data->sprites[PISTOL_BANG]->width / 2 + 10;
// 	data->sprites[PISTOL_BANG]->instances[0].y = data->map.mlx->height - \
// 	data->sprites[PISTOL_BANG]->height + 10;
// 	data->map.mini->instances[0].x = data->map.mlx->width - \
// 	data->map.mini->width;
// 	data->map.mini->instances[0].y = data->map.mlx->height - \
// 	data->map.mini->height;
// }

// void	ft_paintblock(t_data *data, int x, int y, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	x = x * data->map.minimap_scale;
// 	y = y * data->map.minimap_scale;
// 	while (i < data->map.minimap_scale)
// 	{
// 		j = 0;
// 		while (j < data->map.minimap_scale)
// 		{
// 			mlx_put_pixel(data->map.mini, x + i, y + j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	ft_draw_players(t_data *data)
// {
// 	mlx_put_pixel(data->map.mini, data->player.pos.x * data->map.minimap_scale, \
// 	data->player.pos.y * data->map.minimap_scale, 0xFF00FF);
// }

// void	ft_draw_minimap(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (data->map.map_aclean[i])
// 	{
// 		j = 0;
// 		while (data->map.map_aclean[i][j])
// 		{
// 			if (data->map.map_aclean[i][j] == '0' || \
// 			data->map.map_aclean[i][j] == 'N' || \
// 			data->map.map_aclean[i][j] == 'S' || \
// 			data->map.map_aclean[i][j] == 'W' || \
// 			data->map.map_aclean[i][j] == 'E')
// 			{
// 				data->map.map_aclean[i][j] = '0';
// 				ft_paintblock(data, j, i, 0x0000FF);
// 			}
// 			if (data->map.map_aclean[i][j] == ' ')
// 				ft_paintblock(data, j, i, 0x000000);
// 			j++;
// 		}
// 		i++;
// 	}
// 	ft_draw_players(data);
// }
