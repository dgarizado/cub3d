/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:36:08 by dgarizad          #+#    #+#             */
/*   Updated: 2024/01/14 17:59:21 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	leaks(void)
// {
// 	system("leaks cub3D");
// }

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		ft_error(INPUT_NBR);
	ft_memset(&data, 0, sizeof(t_data));
	ft_mapcheck(argv, &data);
	ft_game(&data);
	ft_free_maps(&data);
	ft_free_textures(&data);
	ft_special_abort(data.paths, TEX_COUNT);
	return (0);
}

//atexit(leaks);
