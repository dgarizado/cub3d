/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:36:08 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/21 17:48:26 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leaks(void)
{
	system("leaks cub3d");
}

void	init_intro(mlx_t* mlx, t_data	*data)
{
	data->mlx = mlx;
	/*--------WHAAAAAACHAAAAAAOUUUUUUTTTTTT-------------*/
	data->title.TEMP = data->map.map_aclean;		//IS MAAAAAAAAAAAAAAP
	/*--------------------------------------------------*/
	data->title.screen_width = mlx->width;
	data->title.screen_heigth = mlx->height;
	//data->title.length = data->map.width;  PENDIENTE
	//data->title.heigth = data->map.height;  PENDIENTE
	data->title.boom = 1;
	data->title.title_map = mlx_new_image(mlx, WIDTH_IMG_TITLE_MAP, HEIGTH_IMG_TITLE_MAP);
	data->title.title_img = mlx_new_image(mlx, WIDTH_IMG_TITLE, HEIGHT_IMG_TITLE);
	mlx_texture_t *txt = mlx_load_png("./map_title/start.png");
	data->title.start_img = mlx_texture_to_image(mlx, txt);
	mlx_delete_texture(txt);
	mlx_image_to_window(mlx, data->title.title_img, (WIDTH / 2) - (WIDTH_IMG_TITLE/2), (HEIGHT *0.03));
	mlx_image_to_window(mlx, data->title.title_map, 0, 0);
}

void init_game(t_data *data, mlx_t* mlx)
{
	data->mlx = mlx;
	mlx_image_t* map = mlx_new_image(mlx, (int)(WIDTH_MAP_GAME) , (int)(HEIGHT_MAP_GAME));
	mlx_image_t* game = mlx_new_image(mlx, WIDTH , HEIGHT);
	mlx_image_t *wall_img;
	mlx_image_t *broken;
	mlx_image_t *zombie;
	mlx_image_t *grass;
	mlx_image_t *aura;
	mlx_texture_t *tex;
	tex = mlx_load_png("./textures/wall.png");
	wall_img = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	tex = mlx_load_png("./textures/break.png");
	broken = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	tex = mlx_load_png("./textures/zombie.png");
	zombie = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	tex = mlx_load_png("./textures/grass.png");
	grass = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	tex = mlx_load_png("./textures/aura.png");
	aura = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	data->wall_img = wall_img;
	data->broken = broken;
	data->zombie = zombie;
	data->grass = grass;
	data->aura = aura;
	data->mapp = map;
	data->game = game;
	data->px = 2;//not controled is init in wall!!!
	data->py = 2;//not controled is init in wall!!!
	data->steven_x = 5;//not controled is init in wall!!!
	data->steven_y = 5;//not controled is init in wall!!!
	data->angle=90;
	//data->size = WIDTH/10;//HARDCODEEEEED
	data->screen_width = mlx->width;
	data->screen_heigth = mlx->height;
	mlx_image_to_window(mlx, data->game, 0, 0);
	mlx_image_to_window(mlx, data->mapp, mlx->width * 0.01, mlx->height *0.01);
}

void ft_draw_game(t_data *data)
{
	raycast_game(data->game, data);
}

void hk2(void *d)
{
	t_data *data;

	data = (t_data *)d; 
	if (ft_changed_resolution(data))
	{
		mlx_resize_image(data->mapp, (int)(WIDTH_MAP_GAME), (int)(HEIGHT_MAP_GAME));
		mlx_resize_image(data->game, WIDTH, HEIGHT);
	}
	ft_move_players(data);
	ft_check_door(data);
	ft_memset(data->mapp->pixels, 0, HEIGHT_MAP_GAME* WIDTH_MAP_GAME * sizeof(int));//HARCODED*********************
	ft_memset(data->game->pixels, 0, WIDTH * HEIGHT* sizeof(int));//HARCODED********************
	ft_draw_minimap(data);
	ft_draw_game(data);
}

void	ft_load_intro(mlx_t*mlx, t_data *data)
{
	ft_parse_title(data);//parsear antes del init pues seg fault en ptr a mapa juego
	init_intro(mlx, data);
}

void ft_load_game(mlx_t*mlx, t_data *data)
{

	init_game(data, mlx);
}

void	ft_loop(void *d)
{
	t_data		*data;

	data = (t_data *)d;

	if(data->phase == 0)
	{
		//draw_title_map(data);
		ft_intro_loop(data);
	}
	else if(data->phase == 1)
		hk2(data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	mlx_t*	mlx = mlx_init(1000,1000, "Test", true);
	if (argc != 2)
		ft_error(INPUT_NBR);
	ft_memset(&data, 0, sizeof(t_data));
	ft_mapcheck(argv, &data);
	ft_load_intro(mlx, &data);
	ft_load_game(mlx, &data);
	mlx_loop_hook(mlx, ft_loop, &data);
	//mlx_loop_hook(mlx, hk2, &data);
	mlx_loop(mlx);
	//ft_game(&data);
	//ft_free_maps(&data);
	//ft_free_textures(&data);
	//ft_special_abort(data.paths, TEX_COUNT);
	//atexit(leaks);
	return (0);
}
