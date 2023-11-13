/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:24:27 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/13 20:47:08 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	ft_images_to_window(t_data *data)
{
	mlx_image_to_window(data->map.mlx, data->sprites[PISTOL_BANG], \
	data->map.width*PPC/2 - data->sprites[PISTOL_BANG]->width/2 + 10, \
	data->map.height*PPC - data->sprites[PISTOL_BANG]->height + 10);
	data->sprites[PISTOL_BANG]->instances[0].enabled = false;
	mlx_image_to_window(data->map.mlx, data->sprites[PISTOL], \
	data->map.width*PPC/2 - data->sprites[PISTOL]->width/2, \
	data->map.height*PPC - data->sprites[PISTOL]->height);
}

/**
 * @brief This function is used to load the mini sprites
 * that will be used in the game.
 * 
 * @param data 
 */
void	ft_load_minisprites(t_data *data)
{
	mlx_texture_t	*pistol;
	mlx_texture_t	*pistol_bang;
	
	pistol =mlx_load_png("./imgs/pistol.png");
	pistol_bang =mlx_load_png("./imgs/bangbang.png");
	data->textures[TEX_E] = mlx_load_png("./imgs/wall3.png");
	data->sprites[WALL_E] = mlx_texture_to_image(data->map.mlx, \
	data->textures[TEX_E]);
	data->sprites[PISTOL] = mlx_texture_to_image(data->map.mlx, pistol);
	data->sprites[PISTOL_BANG] = mlx_texture_to_image(data->map.mlx, \
	pistol_bang);
	// data->sprites[PISTOL]=scale_down(data->sprites[PISTOL], 4, data);
	ft_images_to_window(data);
	free(pistol->pixels);
	free(pistol);
	free(pistol_bang->pixels);
	free(pistol_bang);
}
