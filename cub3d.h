/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:38:02 by dgarizad          #+#    #+#             */
/*   Updated: 2023/10/29 13:51:46 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "./lib/MLX42/include/MLX42/MLX42.h"
#include "./libft/libft.h"

#define WIDTH 						1800
#define HEIGHT 						1200
#define WIDTH_IMG_TITLE 			WIDTH*0.9
#define HEIGHT_IMG_TITLE 			HEIGHT*0.5
#define WIDTH_IMG_TITLE_MAP			WIDTH_IMG_TITLE *0.5
//#define WIDTH_IMG_TITLE_MAP			((WIDTH - (WIDTH_IMG_TITLE))*0.9)
#define HEIGTH_IMG_TITLE_MAP		((HEIGHT - (HEIGHT_IMG_TITLE)) *0.7)

//# define SCALE_WIDTH_TITLE			WIDTH_IMG_TITLE*0.03
//# define SCALE_HEIGHT_TITLE			HEIGHT_IMG_TITLE*0.1


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
	char	*map_sclean;
	char	**map_aclean;
	int		width;
	int		height;
	int		bytes;
}	t_map;

typedef struct	s_title
{
	char		**arr;
	int			width;
	int			length;
	int			row;
	int			column;
	int			dx;
	int			dy;
}	t_title;

typedef struct	s_player
{
	int		x;
	int		y;
	double	dir;
	double	fov;
}	t_player;


typedef struct s_macro_data
{
	t_map		map;
	t_player	player;
	t_title		title;
	mlx_t* 		mlx;
	mlx_image_t*		img;
	mlx_image_t*		img2;
	int 				plus;
}	t_data;

//MAPCHECK
bool	ft_mapcheck(char **argv, t_data *data);
int		ft_check_colors(t_data *data, int line_reached);
int		ft_check_paths(t_data *data, int line_reached);
int		ft_check_elements(t_data *data, char **elements);
int		ft_parse_elements(t_data *data);

//PHASE 1
void	ft_phase_1(t_data *data, mlx_t* mlx);
void	draw_title_map(t_data *data, mlx_image_t* img2);
//void	draw_title_map(t_data *data);
int		set_color(float y);

//UTILS
void	ft_error(char *err);
void	msg_error(char *err);
void	ft_print_array(char **array);
int		ft_ismap(char *line, char *str);
char	**ft_abort(char **new_array, unsigned int i);

//UTILS2
void	ft_free_maps(t_data *data);
int		ft_arrlen(char **arr);

//TEXTURE PARSING
bool	ft_texture_parse(t_data *data, int i);

//MAPCHECK2
bool	ft_clean_map(t_data *data, int i);
bool	ft_check_chars(t_data *data);

//MAPANAL
bool	ft_map_anal(t_data *data);

//MAPANAL2
void	ft_space_check_aux(t_data *data, int i, int j);




#endif