/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:24:27 by dgarizad          #+#    #+#             */
/*   Updated: 2023/10/25 17:55:14 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_load_minisprites(t_data *data)
{
	data->map.minimap.xpm[WALL] = mlx_load_xpm42("./imgs/block.xpm42");
	data->map.minimap.xpm[EMPTY] = mlx_load_xpm42("./imgs/green.xpm42");
	data->map.minimap.xpm[PLAYER] = mlx_load_xpm42("./imgs/Red.xpm42");
	data->map.minimap.xpm[SPACE] = mlx_load_xpm42("./imgs/Yellow.xpm42");
	data->map.minimap.img[WALL] = mlx_texture_to_image(data->map.mlx, &data->map.minimap.xpm[WALL]->texture);
	data->map.minimap.img[EMPTY] = mlx_texture_to_image(data->map.mlx, &data->map.minimap.xpm[EMPTY]->texture);
	data->map.minimap.img[PLAYER] = mlx_texture_to_image(data->map.mlx, &data->map.minimap.xpm[PLAYER]->texture);
	data->map.minimap.img[SPACE] = mlx_texture_to_image(data->map.mlx, &data->map.minimap.xpm[SPACE]->texture);
}