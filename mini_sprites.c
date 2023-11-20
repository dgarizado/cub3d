/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:24:27 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/17 18:43:30 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	ft_sprites_to_window(t_data *data)
{
	mlx_image_to_window(data->map.mlx, data->sprites[PISTOL_BANG], \
	data->map.width*data->map.ppc/2 - data->sprites[PISTOL_BANG]->width/2 + 10, \
	data->map.height*data->map.ppc - data->sprites[PISTOL_BANG]->height + 10);
	data->sprites[PISTOL_BANG]->instances[0].enabled = false;
	mlx_image_to_window(data->map.mlx, data->sprites[PISTOL], \
	data->map.width*data->map.ppc/2 - data->sprites[PISTOL]->width/2, \
	data->map.height*data->map.ppc - data->sprites[PISTOL]->height);
}

/**
 * @brief Here we load the sprites for the weapons
 * enemys and other stuff that will be used in the game.
 * if you want to do this in a better way, feel free.
 * it can be done in the same way as the textures for the walls.
 * @param data 
 */
void	ft_load_aux(t_data *data)
{
	mlx_texture_t	*pistol;
	mlx_texture_t	*pistol_bang;
	// xpm_t			*enemy;
	
	pistol =mlx_load_png("./imgs/pistol.png");
	pistol_bang =mlx_load_png("./imgs/bangbang.png");
	// enemy =mlx_load_xpm42("./imgs/Rocky.xpm42");
	data->sprites[PISTOL] = mlx_texture_to_image(data->map.mlx, pistol);
	data->sprites[PISTOL_BANG] = mlx_texture_to_image(data->map.mlx, \
	pistol_bang);
	// data->sprites[ENEMY] = mlx_texture_to_image(data->map.mlx, &enemy->texture); 
	ft_sprites_to_window(data);
	free(pistol->pixels);
	free(pistol);
	free(pistol_bang->pixels);
	free(pistol_bang);
}

/**
 * @brief This function is used to load the mini sprites
 * that will be used in the game. Wall textures
 * are treated appart just because they are not 
 * loaded in the same way.
 * Sprites are loaded individually
 * @param data 
 */
void	ft_load_minisprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		data->sprites[i] = mlx_texture_to_image(data->map.mlx, \
		data->textures[i]);
		i++;
	}
	if (data->bonus == true)
		ft_load_aux(data);
}

