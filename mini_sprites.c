/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:24:27 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/11 18:05:05 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_load_minisprites(t_data *data)
{
	mlx_texture_t	*pistol;
	mlx_texture_t	*pistol_bang;
	
	pistol =mlx_load_png("./imgs/pistol.png");
	pistol_bang =mlx_load_png("./imgs/bangbang.png");
	data->player.textures[TEX_E] = mlx_load_png("./imgs/wall3.png");
	data->player.sprites[WALL_E] = mlx_texture_to_image(data->map.mlx, data->player.textures[TEX_E]);
	data->player.sprites[PISTOL] = mlx_texture_to_image(data->map.mlx, pistol);
	data->player.sprites[PISTOL_BANG] = mlx_texture_to_image(data->map.mlx, pistol_bang);
}
