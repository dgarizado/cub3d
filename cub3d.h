/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:38:02 by dgarizad          #+#    #+#             */
/*   Updated: 2023/10/21 12:58:33 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "./lib/MLX42/include/MLX42/MLX42.h"
#include "./libft/libft.h"

# define INPUT_NBR "WRONG NUMBER OF ARGUMENTS\n"
# define INPUT_EXT "Wrong extention"
# define INPUT_OPN "Can't open file or doesn't exist\n"
# define READ_ERR "Can't read file or is empty\n"

# define BUFFER_SIZE 70
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RST "\033[0m"

typedef struct	s_map
{
	char	*map_s;
	char	**map_a;
	int		width;
	int		height;
	int		bytes;
}	t_map;

typedef struct	s_player
{
	double	x;
	double	y;
	double	dir;
	double	fov;
}	t_player;

typedef struct s_macro_data
{
	t_map		map;
	t_player	player;
}	t_data;


//MAPCHECK
bool	ft_mapcheck(char **argv, t_data *data);

//UTILS
void	ft_error(char *err);
void	ft_print_array(char **array);

#endif