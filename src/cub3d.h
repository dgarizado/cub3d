/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:38:02 by dgarizad          #+#    #+#             */
/*   Updated: 2024/01/14 18:12:06 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define INPUT_NBR "WRONG NUMBER OF ARGUMENTS\n"
# define INPUT_EXT "Wrong extention"
# define INPUT_OPN "Can't open file or doesn't exist\n"
# define READ_ERR "Can't read file or is empty\n"

# define BUFFER_SIZE 70
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RST "\033[0m"
# define YELLOW "\033[0;33m"
# define FOV 60
# define PPC 40
# define WIDTH 1400
# define HEIGHT 800
# define MOVE_SPEED 0.067
# define MINIMAP_SCALE 12
# define NORTH 0
# define EAST 1
# define FLOOR 0
# define CEILING 1

typedef enum e_sprites
{
	WALL_N,
	WALL_S,
	WALL_E,
	WALL_W,
	PISTOL,
	PISTOL_BANG,
	ENEMY,
	BAULT,
	DOOR,
	SPRITES_COUNT
}	t_sprites;

typedef enum e_textures
{
	TEX_N,
	TEX_S,
	TEX_E,
	TEX_W,
	TEX_COUNT
}	t_textures;

typedef struct s_victor
{
	double	x;
	double	y;
}	t_victor;

typedef struct s_ray_charles
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		x;
	double	drawstart;
	double	drawend;
	int		lineheight;
}	t_ray_charles;

typedef struct s_map
{
	char		*map_s;
	char		**map_a;
	char		*map_sclean;
	char		**map_aclean;
	int			width;
	int			height;
	int			bytes;
	int			ppc;
	int			minimap_scale;
	int			colors[2];
	mlx_t		*mlx;
	mlx_image_t	*img3d;
	mlx_image_t	*mini;
}	t_map;

typedef struct s_player
{
	t_victor	pos;
	t_victor	vdir;
	t_victor	plane;
	int			mouse_x;
	int			mouse_y;
	int			vertical;
	double		step_v;
	int			step_count;
}	t_player;

typedef struct s_macro_data
{
	t_map			map;
	t_player		player;
	t_ray_charles	ray;
	mlx_image_t		*sprites[SPRITES_COUNT];
	mlx_texture_t	*textures[TEX_COUNT];
	char			*paths[TEX_COUNT];
	bool			bonus;
}	t_data;

//RENDER
void		drawline(t_data *data, int flag);
void		drawlinetexture(double x1, int column_texture, t_data *data);
void		ray_render(t_data *data);

//MAPCHECK
bool		ft_mapcheck(char **argv, t_data *data);
int			ft_check_colors(t_data *data, int line_reached);
int			ft_check_paths(t_data *data, int line_reached);

//PARSING_ELEMENTS
int			ft_parse_elements(t_data *data);
int			ft_check_elements(t_data *data, char **elements);
void		ft_special_abort(char **arr, int len);

//UTILS
void		ft_error(char *err);
void		msg_error(char *err);
void		ft_print_array(char **array);
int			ft_ismap(char *line, char *str);
char		**ft_abort(char **new_array, unsigned int i);

//UTILS2
uint32_t	apply_shading(t_data *data, uint8_t r, uint8_t g, uint32_t color);
void		ft_free_maps(t_data *data);
int			ft_arrlen(char **arr);
void		ft_free_textures(t_data *data);

//TEXTURE PARSING
bool		ft_texture_parse(t_data *data, int flag);

//MAPCHECK2
bool		ft_clean_map(t_data *data, int i);
bool		ft_check_chars(t_data *data);

//MAPANAL
bool		ft_map_anal(t_data *data);

//MAPANAL2
void		ft_space_check_aux(t_data *data, int i, int j);

//GAME
void		ft_game(t_data *data);

//GAME_AUX
void		ft_draw_minimap(t_data *data);
void		ft_paintblock(t_data *data, int x, int y, int color);
void		ft_fix_images(t_data *data);

//MINISPRITES
void		ft_load_minisprites(t_data *data);

//RAY BAN
void		ray_bang(t_data *data);
void		rotate_victor(t_victor *victor, double angle);

//MOVEMENTS
void		verticals_w(t_data *data);
void		verticals_s(t_data *data);
void		laterals_a(t_data *data);
void		laterals_d(t_data *data);
void		mouse(t_data *data);

#endif