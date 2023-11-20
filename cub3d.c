/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:36:08 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/11 12:22:09 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void leaks(void)
// {
// 	system("leaks cub3d");
// }

int	main(int argc, char **argv)
{
	t_data	data;
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);

	//if (argc != 2)
	//	ft_error(INPUT_NBR);
	//ft_memset(&data, 0, sizeof(t_data));
	//ft_mapcheck(argv, &data);
	//ft_phase_1(&data, mlx);
	ft_phase_2(&data, mlx);//work on map_a and set atributes game
	//ft_phase_3(&data);
	//mlx_loop_hook(mlx, draww, &data);//SAltamos
	mlx_loop_hook(mlx,hk2, &data);
	
	mlx_loop(mlx);
	
	//ft_free_maps(&data);
	//atexit(leaks);
	return (0);
}
