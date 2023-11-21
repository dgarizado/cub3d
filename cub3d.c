/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:36:08 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/21 12:07:35 by vcereced         ###   ########.fr       */
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

void	ft_load_intro(mlx_t*mlx, t_data *data)
{
	ft_parse_title(data);//parsear antes del init pues seg fault en ptr a mapa juego
	init_intro(mlx, data);
}

void	ft_loop(void *d)
{
	t_data		*data;

	data = (t_data *)d;

	draw_title_map(data);
	ft_intro_loop(data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	mlx_t*	mlx = mlx_init(1600,1200, "Test", true);
	if (argc != 2)
		ft_error(INPUT_NBR);
	ft_memset(&data, 0, sizeof(t_data));
	ft_mapcheck(argv, &data);
	ft_load_intro(mlx, &data);
	
	mlx_loop_hook(mlx, ft_loop, &data);
	mlx_loop(mlx);
	//ft_game(&data);
	//ft_free_maps(&data);
	//ft_free_textures(&data);
	//ft_special_abort(data.paths, TEX_COUNT);
	//atexit(leaks);
	return (0);
}
