#ifndef CUB3D_H
# define CUB3D_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
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

#define WIDTH 				data->mlx->width
#define HEIGHT 				data->mlx->height
# define HEIGHT_MAP_GAME    (int)(HEIGHT *0.3)
# define WIDTH_MAP_GAME     (int)(WIDTH *0.3)
# define SCALE_X			(WIDTH_MAP_GAME/data->largoMapa)
# define SCALE_Y			(HEIGHT_MAP_GAME/data->anchoMapa)

# define DIST_FACTOR 0.05 
# define DIST_FACTOR_STEVEN 0.01
# define RENDER_DISTANCE 500/data->size


typedef struct s_bonus
{
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
	int			type_wall;//1 wall 8 roto 7 zombie
	/*----------------------------------*/
	t_bonus		bonus;
/*------------------------------------------*/
}	t_cast;



typedef struct s_macro_data
{
	t_cast		cast;
	mlx_t* mlx;
	mlx_image_t* map;
	mlx_image_t* game;
	mlx_image_t* wall_img;
	mlx_image_t* broken;
	mlx_image_t* zombie;
	mlx_image_t* grass;
	mlx_image_t* aura;
	double 		px;
	double 		py;
	double 		steven_x;
	double 		steven_y;
	double 		angle_steven;
	double 		angle;
	/*----------------DEPENDIENTE DE PARSE--------------------*/
	int* 		arr;
	int			largoMapa;
	int			anchoMapa;
	/*-----------------------------------*/
	int 		size;
	int			screen_width;
	int			screen_heigth;


}	t_data;

void drawLine(double x1, double y1, double x2, double y2, int color, mlx_image_t *ptr, t_data *data);
double 			ft_degre_to_radian(double degre);
double 			radianes_a_grados(double radianes);
unsigned int 	rgbaToHex(int r, int g, int b);
int 			oscurecerColor(int color, char nuevoAlpha);
void 			ft_move_players(t_data *data);
void 			draw_raycast_map(mlx_image_t *map, t_data *data);
void 			raycast_game(mlx_image_t *game, t_data *data);
void 			ft_draw_minimap(t_data *data);
void draw_steven_sprite(t_data *data);
float fix_fish_eye(float distance, float angle, float angle_player);
void ft_check_door(t_data *data);
float rays(mlx_image_t *map, t_data *data, float angle);
int	detras_de_steven_bonus( t_data *data, int n, float angle);
void drawLineTexture_bonus(double x1, double y1, double y2, int column_texture, t_data *data, int n);
void normalize_angle(double *angulo_me, double *angle_steven_from_me);
int last_colision_arr(int *arr);

int into_limits(t_data *data);
int get_value_map(t_data *data);
void set_params_colision(int n, t_data *data);
int	ft_changed_resolution(t_data *data);
#endif