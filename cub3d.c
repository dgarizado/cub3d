/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:36:08 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/24 14:15:52 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leaks(void)
{
	system("leaks cub3d");
}

void	put_images_to_windows(t_data *data, mlx_t *mlx)
{
	mlx_image_to_window(mlx, data->img[GAME], 0, 0);
	mlx_image_to_window(mlx, data->img[MINIMAP_GAME], WIDTH * 0.01, HEIGHT * 0.01);
	mlx_image_to_window(mlx, data->img[TITLE_INTRO], (WIDTH / 2) - (WIDTH_IMG_TITLE / 2), (HEIGHT * 0.03));
	mlx_image_to_window(mlx, data->img[MAP_INTRO], 0, 0);
}
void	load_graphics(mlx_t *mlx, t_data *data)
{
	data->img[TITLE_INTRO] = mlx_new_image(mlx, WIDTH_IMG_TITLE, HEIGHT_IMG_TITLE);
	data->img[MAP_INTRO] = mlx_new_image(mlx, WIDTH_IMG_TITLE_MAP, HEIGTH_IMG_TITLE_MAP);
	data->img[MINIMAP_GAME] = mlx_new_image(mlx, (int)(WIDTH_MAP_GAME), (int)(HEIGHT_MAP_GAME));
	data->img[GAME] = mlx_new_image(mlx, WIDTH, HEIGHT);
	//------------SEG FAULT SI NO ASIGNA WALLS SE SUPONE QUE SE SETEA EN PARSEO*****************************
	data->textures[WALL_N] = mlx_load_png(data->paths[PATH_N]);
	data->textures[WALL_S] = mlx_load_png(data->paths[PATH_S]);
	data->textures[WALL_E] = mlx_load_png(data->paths[PATH_E]);
	data->textures[WALL_W] = mlx_load_png(data->paths[PATH_W]);
	data->textures[WALL_TO_BROKE] = mlx_load_png("./imgs/wall_to_broke.png");
	data->textures[ENEMY] = mlx_load_png("./imgs/zombie.png");
	data->textures[AURA] = mlx_load_png("./imgs/aura.png");
	data->textures[GRASS] = mlx_load_png("./imgs/grass.png");
	data->textures[BROKEN] = mlx_load_png("./imgs/break.png");
	data->textures[START_INTRO] = mlx_load_png("./imgs/start.png");
	ft_load_minisprites(data);
	ft_free_textures(data);//*************************CUIDDAAAAADDOOOOOOOO
}

void	init_params(mlx_t *mlx, t_data	*data)
{
	data->mlx = mlx;
	data->screen_width = mlx->width;
	data->screen_heigth = mlx->height;
	data->title.boom = 1;
}

void	ft_load(mlx_t*mlx, t_data *data)
{
	ft_parse_title(data);
	init_params(mlx, data);
	load_graphics(mlx, data);
	put_images_to_windows(data, mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;
	mlx_t	*mlx;

	mlx = mlx_init(1000, 1000, "Test", true);
	if (argc != 2)
		ft_error(INPUT_NBR);
	ft_memset(&data, 0, sizeof(t_data));
	ft_mapcheck(argv, &data);
	ft_load(mlx, &data);
	mlx_loop_hook(mlx, ft_loop, &data);
	mlx_loop(mlx);
	//ft_game(&data);
	//ft_free_maps(&data);
	//ft_free_textures(&data);
	//ft_special_abort(data.paths, TEX_COUNT);
	//atexit(leaks);
	return (0);
}
