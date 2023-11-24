/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:10:37 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/24 17:09:21 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*choose_orientation(int j, t_data *data)
{
	if (data->cast.bonus.flag_bonus[j] == 'x' && \
	data->cast.bonus.cell_step_bonus[j] == -1)
		return (data->sprites[WALL_W]);
	else if (data->cast.bonus.flag_bonus[j] == 'x' \
	&& data->cast.bonus.cell_step_bonus[j] == 1)
		return (data->sprites[WALL_E]);
	else if (data->cast.bonus.flag_bonus[j] == 'y' \
	&& data->cast.bonus.cell_step_bonus[j] == -1)
		return (data->sprites[WALL_N]);
	else if (data->cast.bonus.flag_bonus[j] == 'y' \
	&& data->cast.bonus.cell_step_bonus[j] == 1)
		return (data->sprites[WALL_S]);
	return (NULL);
}

mlx_image_t	*choose_image(t_data *data)
{
	mlx_image_t	*img;
	int			n;

	n = data->cast.bonus.n;
	if (n == -1)
		img = data->sprites[ENEMY];
	else if (data->cast.bonus.type_wall_bonus[n] == '1')
		img = choose_orientation(n, data);
	else if (data->cast.bonus.type_wall_bonus[n] == '9')
		img = data->sprites[WALL_TO_BROKE];
	else if (data->cast.bonus.type_wall_bonus[n] == 'B')
		img = data->sprites[BROKEN];
	else if (data->cast.bonus.type_wall_bonus[n] == 'V')
		img = data->sprites[VROKEN];
	else if (data->cast.bonus.type_wall_bonus[n] == 'D')
		img = data->sprites[DOOR];
	else if (data->cast.bonus.type_wall_bonus[n] == 'O')
		img = data->sprites[OPEN];
	else if (data->cast.bonus.type_wall_bonus[n] == 'G')
		img = data->sprites[GRASS];
	else if (data->cast.bonus.type_wall_bonus[n] == 'A')
		img = data->sprites[AURA];
	return (img);
}

int	ft_recalibrate_offset(double *y2, double *y1, t_data *data)
{
	int	offsety1;

	offsety1 = (int)(fabs(*y1));
	*y1 = 0;
	*y2 = WIDTH;
	return (offsety1);
}

void	ft_draw_texture(int *arr, float y_texture, mlx_image_t *img, t_data *d)
{
	uint32_t	color;
	int			row_texture;	

	row_texture = floor(y_texture * arr[2]);
	color = ((uint32_t *)img->pixels)[(row_texture * img->width) \
	+ (d->column_texture)];
	if (color != 0)
		((uint32_t *)d->img[GAME]->pixels)[((int)(arr[1]) *\
		d->img[GAME]->width + (int)(arr[0]))] = color;
}

void	drawlinetexture_bonus(double x1, double y1, double y2, t_data *data)
{
	double			steps;
	float			step_y_texture;
	mlx_image_t		*img;
	int				arr[3];

	img = choose_image(data);
	steps = fabs(y2 - y1);
	step_y_texture = (float)img->height / (float)steps;
	arr[2] = 0;
	if ((int)(y2) > HEIGHT)
		arr[2] = ft_recalibrate_offset(&y2, &y1, data);
	arr[0] = x1;
	arr[1] = y1;
	while ((int)fabs(y2 - arr[1]))
	{
		if (arr[0] >= 0 && arr[0] <= WIDTH && arr[1] >= 0 && arr[1] <= HEIGHT)
			ft_draw_texture(arr, step_y_texture, img, data);
		(arr[1])++;
		(arr[2])++;
	}
}
