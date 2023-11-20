#include "cub3d.h"

void ft_draw_game(t_data *data)
{
	raycast_game(data->game, data);
}

void hk2(void *d)
{
	t_data *data;

	data = (t_data *)d; 
	ft_move_players(data);
	ft_check_door(data);
	if (ft_changed_resolution(data))
	{
		mlx_resize_image(data->map, (int)(WIDTH_MAP_GAME), (int)(HEIGHT_MAP_GAME));
		mlx_resize_image(data->game, WIDTH, HEIGHT);
	}
	ft_memset(data->map->pixels, 0, HEIGHT_MAP_GAME* WIDTH_MAP_GAME * sizeof(int));//HARCODED*********************
	ft_memset(data->game->pixels, 0, WIDTH * HEIGHT* sizeof(int));//HARCODED********************
	ft_draw_minimap(data);
	ft_draw_game(data);
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
	tex = mlx_load_png("./textures/break.png");
	broken = mlx_texture_to_image(mlx, tex);
	tex = mlx_load_png("./textures/zombie.png");
	zombie = mlx_texture_to_image(mlx, tex);
	tex = mlx_load_png("./textures/grass.png");
	grass = mlx_texture_to_image(mlx, tex);
	tex = mlx_load_png("./textures/aura.png");
	aura = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	data->wall_img = wall_img;
	data->broken = broken;
	data->zombie = zombie;
	data->grass = grass;
	data->aura = aura;
	data->map = map;
	data->game = game;
	data->px = 2;//not controled is init in wall!!!
	data->py = 2;//not controled is init in wall!!!
	data->steven_x = 5;//not controled is init in wall!!!
	data->steven_y = 5;//not controled is init in wall!!!
	data->angle=90;
	data->size = WIDTH/10;
	data->screen_width = mlx->width;
	data->screen_heigth = mlx->height;
	//if (data->largoMapa > data->anchoMapa)
	//	data->size = WIDTH_MAP_GAME/data->largoMapa;//HARCODED!
	//else
	//	data->size = WIDTH_MAP_GAME/data->anchoMapa;
}
int	main(void)
{
	mlx_t* mlx = mlx_init(2000, 1000, "Test", true);
	t_data data;
	int arr[] = {1,1,1,1,1,1,1,1,1,1,
				 1,0,0,0,0,0,0,0,0,1,
			   	 1,0,0,0,6,0,0,0,0,1,
				 1,0,0,0,0,0,0,6,0,1,
				 1,0,0,9,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,0,0,1,
				 1,0,6,0,0,0,0,6,0,1,
			   	 1,0,0,0,0,0,0,0,0,1,
				 1,1,1,1,1,1,1,1,1,1};
	data.arr = arr;
	data.largoMapa = 10;//ADAPTAR A PARSEO!!!
	data.anchoMapa = 10;//ADAPTAR A PARSEO!!!
	init_game(&data, mlx);
	mlx_image_to_window(mlx, data.map, mlx->width * 0.05, mlx->height *0.05);
	mlx_image_to_window(mlx, data.game, 0, 0);
	mlx_loop_hook(mlx, hk2, &data);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}