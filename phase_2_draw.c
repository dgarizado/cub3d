/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase_2_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:14:06 by vcereced          #+#    #+#             */
/*   Updated: 2023/11/05 12:03:23 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_link_person(t_data *data, int column, int row)
{
	mlx_texture_t *link;
	mlx_image_t *linkimg;

	link = mlx_load_png("./texture_link/link.png");
	linkimg = mlx_texture_to_image(data->mlx, link);
//mlx_image_to_window(data->mlx, linkimg, (column * (data->map.atr.scale_width_mini_map / 10)), (row * (data->map.atr.scale_height_mini_map/10)));
	
}

void	draw_cuadrado(t_data *data, int column, int row, int color)
{
	int start_square_x;
	int start_square_y;

	int y;
	int x;
	y = 0;
	//esto es los topes para dibujar un cuadradito
	while(y < data->map.atr.scale_height_mini_map/10)//harcoded; a 7 puntos y
	{
		x = 0;
		while( x < data->map.atr.scale_width_mini_map/10)//harcoded a 7 puntos x
		{
			start_square_y = (row * (data->map.atr.scale_height_mini_map/10));
			start_square_x = (column * (data->map.atr.scale_width_mini_map / 10));
			int z = 0;
			//while(z <= 15)//profundidad HARDCODED
		//	{
		//		mlx_put_pixel(data->game,x + start_square_x + z, y + start_square_y + z, 0x9b9b9bFF);
		//		z++;
		//	}
			mlx_put_pixel(data->game, x + start_square_x, y + start_square_y, color);
			x++;
		}
		y++;
	}
}
//empieza en el map de numeros en la posicion parcial posible max.arriba3 max.izq3 y iterar buscando unos y pintando

void	draw_partial_mmap(t_data *data, int column, int row, int color)
{
	int tope_row;
	int relative_row;//7x7 minimap
	int tope_column;
	int relative_column;
	int start_column;
	
	tope_row = row + 7;
	tope_column = column + 7;
	start_column = column;
	relative_row = 0;
	if (data->player.y == 2)//adjust gap top gap left cuidado no la cuadricula es 7x7, entonces si mandas row 7 segfault
		relative_row++;
	if (data->player.y == 1)
		relative_row +=2;
	while(row < tope_row && row < data->map.ancho && relative_row <7)
	{
		column = start_column;
		relative_column =  0;
		if (data->player.x == 2)//adjust gap top gap left
			relative_column++;
		if (data->player.x == 1)
			relative_column +=2;
		while( relative_column <7 && column < tope_column && column < data->map.largo)
		{
			if(data->map.map[(row * data->map.largo) + column] == 49)// busca la row y column real en el mapa
			{
			//	printf("cuadrado a pintar posiciones relativas al centro \nrow %d column %d", row, column);
				draw_cuadrado(data, relative_column, relative_row,  0xBA55D3FF);
			}
			else if(relative_column == 3 && relative_row == 3)//muñeco pintar para que se cubra o se vea sobre los objetos pa ke se pinte en su momento
				mlx_draw_texture(data->game, data->linktexture, (3 * (data->map.atr.scale_width_mini_map / 10)), (3 * (data->map.atr.scale_height_mini_map/10)));
			relative_column++;
			column++;
		}
		relative_row++;
		row++;
	}

}
//descubrir hasta -3Left -3 up posibles
void draw(t_data * data, int row, int column, int color)
{
	int cont;

	cont = 3;
	while(row > 0 && cont > 0)
	{
		row--;
		cont--;
	}
	cont = 3;
	while(column > 0 && cont > 0)
	{
		column--;
		cont--;
	}
	//printf("a menos 3 de N row %d column %d", row, column);
	draw_partial_mmap(data, column, row, color);
}

void	ft_game_little_map(t_data *data)// el truco para el link es saber si pintar primero game/ link o link/game
{
	draw(data, data->player.y, data->player.x, 0x999999FF);//dibuja en bits game
	draw_vision(data);
	//mlx_image_to_window(data->mlx, data->game, 0, HEIGHT * 0.8);
}