/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:38:02 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/24 19:40:49 by vcereced         ###   ########.fr       */
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

#define HEIGHT						data->mlx->height
#define WIDTH 						data->mlx->width
#define WIDTH_IMG_TITLE 			data->mlx->width * 0.9
#define HEIGHT_IMG_TITLE 			data->mlx->height * 0.4
#define WIDTH_IMG_TITLE_MAP			data->mlx->width
#define HEIGTH_IMG_TITLE_MAP		data->mlx->height
# define HEIGHT_MAP_GAME    (int)(HEIGHT * 0.3)
# define WIDTH_MAP_GAME     (int)(WIDTH * 0.3)
# define SCALE_X			(WIDTH_MAP_GAME/data->map.width)
# define SCALE_Y			(HEIGHT_MAP_GAME/data->map.height)
# define DIST_FACTOR 0.05 
# define DIST_FACTOR_STEVEN 0.01

# define BUFFER_SIZE 70


# define INPUT_NBR "WRONG NUMBER OF ARGUMENTS\n"
# define INPUT_EXT "Wrong extention"
# define INPUT_OPN "Can't open file or doesn't exist\n"
# define READ_ERR "Can't read file or is empty\n"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RST "\033[0m"
# define YELLOW "\033[0;33m"
# define FOV 60
# define PPC 40
# define MOVE_SPEED 0.05
# define MINIMAP_SCALE 12
# define NORTH 0
# define EAST 1
# define FLOOR 0
# define CEILING 1

typedef enum e_sprites{
	WALL_N,
	WALL_S,
	WALL_E,
	WALL_W,
	WALL_TO_BROKE,
	//PISTOL,
	//PISTOL_BANG,
	ENEMY,
	AURA,
	DOOR,
	OPEN,
	GRASS,
	BROKEN,
	VROKEN,
	START_INTRO,
	SPRITES_COUNT
} t_sprites;

typedef enum e_img{
	TITLE_INTRO,
	MAP_INTRO,
	MINIMAP_GAME,
	GAME,
	IMG_COUNT
} t_img;

typedef enum e_path{
	PATH_N,
	PATH_S,
	PATH_E,
	PATH_W,
	PATH_COUNT
} t_path;

typedef struct s_coord{
	int last_y;
	int last_x;
	int x;
	int y;
	int x1;
	int y1;
	int x2;
	int y2;
} t_coord;

typedef struct	s_map
{
	char		*map_s;
	char		**map_a;
	char		*map_sclean;
	char		**map_aclean;
	int			width;
	int			height;
	int			bytes;
	int			colors[2];
	int			flag;
}	t_map;

typedef struct	s_title
{
	char				**arr;
	int 				color_up;
	int					flag;
	int					heigth;
	int					length;
	float 				boom;
}	t_title;

typedef struct s_bonus
{
	int			n;
	int 		cell_step_bonus[10];
	int 		current_cell_bonus[10];
	char 		flag_bonus[10];
	int			type_wall_bonus[10];
	float 		distance[10];
}	t_bonus;

typedef struct s_cast
{
	float 	ray_length;
	int 	cell_x_step;
	float 	ray_x_start;
	float 	ray_x_direction;
	float 	ray_x_unit_length;
	float 	ray_x_length;
	int 	current_x_cell;
	int 	cell_y_step;
	float 	ray_y_start;
	float 	ray_y_direction;
	float 	ray_y_unit_length;
	float 	ray_y_length;
	int 	current_y_cell;
	int 		cell_step;
	int 		current_cell;
	char 		flag;
	int			type_wall;
	t_bonus		bonus;
}	t_cast;

typedef struct s_macro_data
{
	mlx_t			*mlx;
	t_title			title;
	t_map			map;
	t_coord			coord;
	mlx_texture_t	*textures[SPRITES_COUNT];
	mlx_image_t		*sprites[SPRITES_COUNT];
	mlx_image_t		*img[IMG_COUNT];
	char 			*paths[PATH_COUNT];
	/*------VICTOR------*/
	t_cast		cast;
	double 		px;
	double 		py;
	double 		steven_x;
	double 		steven_y;
	double 		angle_steven;
	double 		angle;
	int			phase;
	int			column_texture;
	int			zombie;
}	t_data;

//RENDER
void 	draw_title(t_data * data);
void	draw_title_map(t_data *data);
void	ft_draw_minimap(t_data *data);
void	draw_raycast_map(t_data *data);



//MAPCHECK
bool	ft_mapcheck(char **argv, t_data *data);
int		ft_check_colors(t_data *data, int line_reached);
int		ft_check_paths(t_data *data, int line_reached);

//PARSING_ELEMENTS
int		ft_parse_elements(t_data *data);
int		ft_check_elements(t_data *data, char **elements);
void	ft_special_abort(char **arr, int len);

//PARSE TITLE
char	*ft_parse_title(t_data *data);
char 	**ft_skip_sp_arr(char **arr);

//UTILS
void	ft_error(char *err);
void	msg_error(char *err);
void	ft_print_array(char **array);
int		ft_ismap(char *line, char *str);
char	**ft_abort(char **new_array, unsigned int i);

//UTILS2
void	ft_free_maps(t_data *data);
int		ft_arrlen(char **arr);
void	ft_free_textures(t_data *data);

//***UTILS
int		set_color(float y, t_data *data);
double	ft_degre_to_radian(double degre);
double	radian_to_grade(double radianes);
void	normalize_angle(double *angulo_me, double *angle_steven_from_me);
int		into_limits(t_data *data);

//TEXTURE PARSING
bool	ft_texture_parse(t_data *data, int flag);

//MAPCHECK2
bool	ft_clean_map(t_data *data, int i);
bool	ft_check_chars(t_data *data);

//MAPANAL
bool	ft_map_anal(t_data *data);

//MAPANAL2
void	ft_space_check_aux(t_data *data, int i, int j);

//LOOPS
void	ft_loop(void *d);

//DRAWLINE
void	drawlinetexture_bonus(double x1, double y1, double y2, t_data *data);
void 	drawline(t_coord *p, int color, mlx_image_t *ptr, t_data *data);

//MINISPRITES
void	ft_load_minisprites(t_data *data);

//RAYCASTING
float	rays(t_data *data, float angle);
int		get_value_map(t_data *data);
void	raycast_game(t_data *data);
float	fix_fish_eye(float distance, float angle, float angle_player);
int		last_colision_arr(int *arr);
void	set_params_colision(int n, t_data *data);

//ZOMBIE
void	ft_draw_steven(float wallheight, int column, t_data *data);
void	draw_steven_sprite(t_data *data);

//MOVEMENTS
void 	ft_move_players(t_data *data);
void 	ft_check_interaction(t_data *data);
void	ft_check_move(double *temp, double *ptr_x, double *ptr_y, t_data *d);

void	encounter_steven(t_data *data);


#endif