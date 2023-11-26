/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:36:08 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/26 20:36:06 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"

void	leaks(void)
{
	system("leaks cub3D_bonus");
}

void	put_images_to_windows(t_data *data, mlx_t *mlx)
{
	mlx_image_to_window(mlx, data->img[GAME], 0, 0);
	mlx_image_to_window(mlx, data->img[MINIMAP_GAME], WIDTH * 0.01, \
	HEIGHT * 0.01);
	mlx_image_to_window(mlx, data->img[TITLE_INTRO], (WIDTH / 2) - \
	(WIDTH_IMG_TITLE / 2), (HEIGHT * 0.03));
	mlx_image_to_window(mlx, data->img[MAP_INTRO], 0, 0);
	mlx_image_to_window(mlx, data->sprites[PISTOL_BANG], \
	mlx->width / 2 - \
	data->sprites[PISTOL_BANG]->width / 2 +10, \
	mlx->height +10 - data->sprites[PISTOL_BANG]->height);
	data->sprites[PISTOL_BANG]->instances[0].enabled = false;
	mlx_image_to_window(mlx, data->sprites[PISTOL], \
	mlx->width / 2 - \
	data->sprites[PISTOL]->width / 2, \
	mlx->height - data->sprites[PISTOL]->height);
	data->sprites[PISTOL]->instances[0].enabled = false;
}

void	load_graphics(mlx_t *mlx, t_data *data)
{
	data->img[TITLE_INTRO] = mlx_new_image(mlx, WIDTH_IMG_TITLE, \
	HEIGHT_IMG_TITLE);
	data->img[MAP_INTRO] = mlx_new_image(mlx, WIDTH_IMG_TITLE_MAP, \
	HEIGTH_IMG_TITLE_MAP);
	data->img[MINIMAP_GAME] = mlx_new_image(mlx, (int)(WIDTH_MAP_GAME), \
	(int)(HEIGHT_MAP_GAME));
	data->img[GAME] = mlx_new_image(mlx, WIDTH, HEIGHT);
	data->textures[WALL_TO_BROKE] = mlx_load_png("./imgs/wall_to_broke.png");
	data->textures[ENEMY] = mlx_load_png("./imgs/zombie.png");
	data->textures[AURA] = mlx_load_png("./imgs/aura.png");
	data->textures[GRASS] = mlx_load_png("./imgs/grass.png");
	data->textures[BROKEN] = mlx_load_png("./imgs/break.png");
	data->textures[DOOR] = mlx_load_png("./imgs/door.png");
	data->textures[OPEN] = mlx_load_png("./imgs/open.png");
	data->textures[VROKEN] = mlx_load_png("./imgs/break2.png");
	data->textures[START_INTRO] = mlx_load_png("./imgs/start.png");
	data->textures[PISTOL] = mlx_load_png("./imgs/pistol.png");
	data->textures[PISTOL_BANG] = mlx_load_png("./imgs/bangbang.png");
	data->textures[ENEMY2] = mlx_load_png("./imgs/zombieb.png");
	ft_load_minisprites(data);
}

void	init_params(mlx_t *mlx, t_data	*data)
{
	data->mlx = mlx;
	data->title.boom = 1;
}

void	ft_load(mlx_t*mlx, t_data *data)
{
	ft_parse_title(data);
	init_params(mlx, data);
	load_graphics(mlx, data);
	put_images_to_windows(data, mlx);
}

void ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*d;
	float	x;
	float	y;

	d = (t_data *)param;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		ft_check_interaction(d);
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
	mlx_key_hook(mlx, ft_key_hook, &data);
	mlx_loop(mlx);
	ft_abort(data.title.arr, ft_arrlen(data.title.arr));
	ft_free_maps(&data);
	ft_free_textures(&data);
	ft_special_abort(data.paths, PATH_COUNT);
	//atexit(leaks);
	return (0);
}
