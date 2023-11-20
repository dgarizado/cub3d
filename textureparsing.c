/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureparsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:48:22 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/04 18:05:22 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_texture_parse(t_data *data, int i)
{
	printf("Texture parsing\n");
	printf("data->map.map_a[%d] = '%s'\n", i, data->map.map_a[i]);
	//getchar();
	return (true);
}