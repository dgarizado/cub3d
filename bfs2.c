/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:04:38 by dgarizad          #+#    #+#             */
/*   Updated: 2023/10/22 17:22:37 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Gets the last node of the queue.
 * Returns a pointer to the last node of the queue.
 * @param lst 
 * @return t_queue* 
 */
t_queue	*ft_getlast(t_queue *lst)
{
	while (lst)
	{
		if (!(lst -> next))
			return (lst);
		lst = lst ->next;
	}
	return (NULL);
}

/**
 * @brief Adds a new node to the queue in the last position.
 * this stack is a FIFO queue.
 * @param lst 
 * @param newn 
 */
void	ft_add_back(t_queue *lst, t_queue *newn)
{
	t_queue	*ptr;

	ptr = ft_getlast(lst);
	if (!ptr)
		lst = newn;
	else
		ptr->next = newn;
}

/**
 * @brief Creates a new node for the queue.
 * 
 * @param content  Coordinates of the node to be created.
 * @param queue 
 * @return t_queue* 
 */
t_queue	*ft_newqueue(void *content, t_queue *queue)
{
	t_queue	*new_node;

	new_node = malloc(sizeof(t_queue));
	if (!new_node)
		return (NULL);
	new_node->row = ((int *)content)[0];
	new_node->col = ((int *)content)[1];
	new_node -> next = NULL;
	new_node->visited = queue->visited;
	return (new_node);
}

/**
 * @brief Allocates a new node that contains location info
 * for the visited "pixels". It is a FIFO queue.
 * @param queue 
 * @param row 
 * @param col 
 * @return int 
 */
int	ft_add2queue(t_queue *queue, int row, int col)
{
	t_queue	*new;
	int		coords[2];

	coords[0] = row;
	coords[1] = col;
	(queue->visited)[row][col] = 'Q';
	new = ft_newqueue(coords, queue);
	ft_add_back(queue, new);
	return (0);
}
