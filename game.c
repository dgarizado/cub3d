/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:18:54 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/13 21:50:26 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

void    ft_keyhook(mlx_key_data_t keydata, void *param)
{
    t_data *data;

    data = param;

    if (keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(data->map.mlx);
    if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
    {
        data->map.mini->instances[0].enabled ^= true;
    }
}

void    ft_hook2(void *param)
{
	t_data	*data;

	data = param;
	verticals_w(data);
	verticals_s(data);
	laterals_a(data);
	laterals_d(data);
	mouse(data);
	if (mlx_is_mouse_down(data->map.mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		data->sprites[PISTOL]->instances[0].enabled = false;
		data->sprites[PISTOL_BANG]->instances[0].enabled = true;
	}
	}

void    ft_hook(void *param)
{
	t_data  *data;
	double	start;
	double	end;
	double	elapsed;

	data = param;
	start = (double)clock() / CLOCKS_PER_SEC;
	ray_bang(data);
	if (mlx_is_key_down(data->map.mlx, MLX_KEY_RIGHT))
	{
		rotate_victor(&data->player.vdir, 1);
		rotate_victor(&data->player.plane, 1);
	}
	if (mlx_is_key_down(data->map.mlx, MLX_KEY_LEFT))
	{
		rotate_victor(&data->player.vdir, -1);
		rotate_victor(&data->player.plane, -1);
	}
	end = (double)clock() / CLOCKS_PER_SEC;
	if (end - start < 0.016)
	{
		elapsed = 0.016 - (end - start);
		usleep(elapsed * 1000000);
	} 	
}

void ft_paintblock(t_data *data, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	x = x * MINIMAP_SCALE;
	y = y * MINIMAP_SCALE;
	while(i < MINIMAP_SCALE)
	{
		j = 0;
		while(j < MINIMAP_SCALE)
		{
			mlx_put_pixel(data->map.mini, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void ft_draw_minimap(t_data *data)
{
	int i;
	int j;
	i = 0;
	while (data->map.map_aclean[i])
	{
		j = 0;
		while (data->map.map_aclean[i][j])
		{
			if (data->map.map_aclean[i][j] == '0' || \
			data->map.map_aclean[i][j] == 'N' || \
			data->map.map_aclean[i][j] == 'S' || \
			data->map.map_aclean[i][j] == 'W' || \
			data->map.map_aclean[i][j] == 'E')
				ft_paintblock(data, j, i, 0x0000FF);
			if (data->map.map_aclean[i][j] == ' ')
				ft_paintblock(data, j, i, 0x000000);
			j++;
		}
		i++;
	}
	mlx_put_pixel(data->map.mini, data->player.pos.x*MINIMAP_SCALE , \
	data->player.pos.y*MINIMAP_SCALE , 0xFF00FF);

}

void ft_draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	err = dx - dy;
	if (x1 < x2)
		sx = 1;
	else
		sx = -1;
	if (y1 < y2)
		sy = 1;
	else
		sy = -1;
	while (x1 != x2 || y1 != y2)
	{
		if (x1 >= 0 && x1 < (int)img->width && y1 >= 0 && y1 < (int)img->height)
			mlx_put_pixel(img, x1, y1, color);
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

int mlx_get_pixel(mlx_image_t *img, int x, int y)
{
	int color;
	int i;

	i = 0;
	color = 0;
	if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
	{
		while (i < 4)
		{
			color += img->pixels[(y * img->width + x) * 4 + i] << (8 * i);
			i++;
		}
	}
	return (color);
}

mlx_texture_t *scale_down_texture(mlx_texture_t *tex, int scale)
{
    mlx_texture_t *new_tex;
    int i, j, k, l;
    int r, g, b, color;

    new_tex = malloc(sizeof(mlx_texture_t));
    new_tex->width = tex->width / scale;
    new_tex->height = tex->height / scale;
    new_tex->bytes_per_pixel = tex->bytes_per_pixel;
    new_tex->pixels = malloc(new_tex->width * new_tex->height * new_tex->bytes_per_pixel);

    i = 0;
    while (i < (int)new_tex->height)
    {
        j = 0;
        while (j < (int)new_tex->width)
        {
            k = 0;
            r = g = b = 0;
            while (k < scale)
            {
                l = 0;
                while (l < scale)
                {
                    color = tex->pixels[(j*scale + k) + (i*scale + l)*tex->width];
                    r += (color >> 24) & 0xFF;
                    g += (color >> 16) & 0xFF;
                    b += (color >> 8) & 0xFF;
                    l++;
                }
                k++;
            }
            r /= scale * scale;
            g /= scale * scale;
            b /= scale * scale;
            color = (r << 24) | (g << 16) | (b << 8);
            new_tex->pixels[j + i*new_tex->width] = color;
            j++;
        }
        i++;
    }
    return (new_tex);
}

mlx_image_t *scale_down(mlx_image_t *img, int scale, t_data *data)
{
    mlx_image_t *new_img;
    int i, j, k, l;
    int r, g, b, color;

    new_img = mlx_new_image(data->map.mlx, img->width / scale, img->height / scale);
    i = 0;
    while (i < (int)new_img->height)
    {
        j = 0;
        while (j < (int)new_img->width)
        {
            k = 0;
            r = g = b = 0;
            while (k < scale)
            {
                l = 0;
                while (l < scale)
                {
                    color = mlx_get_pixel(img, j*scale + k, i*scale + l);
                    r += (color >> 16) & 0xFF;
                    g += (color >> 8) & 0xFF;
                    b += color & 0xFF;
                    l++;
                }
                k++;
            }
            r /= scale * scale;
            g /= scale * scale;
            b /= scale * scale;
            color = (r << 16) | (g << 8) | b;
            mlx_put_pixel(new_img, j, i, color);
            j++;
        }
        i++;
    }
    return (new_img);
}

/**
 * @brief Create a mlx_image_t object
 * Creates the render image for the game and
 * the minimap image.
 * @param data 
 */
void    ft_init_graphics(t_data *data)
{
    data->map.mlx = mlx_init(data->map.width * data->map.ppc, data->map.height * data->map.ppc, \
    "Cub3D", true);
    data->map.img3d = mlx_new_image(data->map.mlx,data->map.width * data->map.ppc, \
    data->map.height * data->map.ppc);
    data->map.mini = mlx_new_image(data->map.mlx, data->map.width * MINIMAP_SCALE, \
    data->map.height * MINIMAP_SCALE);
    ft_memset(data->map.mini->pixels, 0xC0, data->map.mini->width * \
    data->map.mini->height * 4);
    mlx_image_to_window(data->map.mlx, data->map.img3d, 0, 0);
    mlx_image_to_window(data->map.mlx, data->map.mini, \
    data->map.width * data->map.ppc - data->map.mini->width, data->map.height * data->map.ppc \
    - data->map.mini->height);  
}

void    ft_game(t_data *data)
{
	data->map.ppc = WIDTH / data->map.width;
	
    ft_init_graphics(data);
    ft_load_minisprites(data);
    ft_draw_minimap(data);
	mlx_set_cursor_mode(data->map.mlx, MLX_MOUSE_HIDDEN);
	mlx_key_hook(data->map.mlx, ft_keyhook, data);
    mlx_loop_hook(data->map.mlx, ft_hook, data);
    mlx_loop_hook(data->map.mlx, ft_hook2, data);
    mlx_loop(data->map.mlx);
    mlx_terminate(data->map.mlx);
}

