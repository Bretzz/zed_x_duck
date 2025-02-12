/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_obj_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:32:19 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/12 18:38:49 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	ft_free_point_list(t_point_list *list);
void	ft_free_obj_list(t_obj_list *obj);
int		ft_lstadd_point_tail(t_point_list **list, t_point_list **tail,
			int color, float value, t_point point);
int		ft_lstadd_obj_tail(t_obj_list *obj_tail, t_point_list **points,
			int color, int value, t_point point);
int		ft_lstnew_obj(t_obj_list **obj);

/* takes a point_list and a point as parameters.
allocate a new node with the data of the point,
then adds the node to the end of the list.
RETURNS: 1 if the node was added correctly, 0 in case of error.
NOTE: if list is NULL the new node is set as the head of the list.*/
int	ft_lstadd_point_tail(t_point_list **list, t_point_list **tail,
	int color, float value, t_point point)
{
	t_point_list	*node;

	node = (t_point_list *)malloc(1 * sizeof(t_point_list));
	if (node == NULL)
		return (0);
	node->point = point;
	node->value = value;
	node->color = color;
	node->next = NULL;
	if (*list == NULL)
	{
		*list = node;
		*tail = node;
		return (1);
	}
	(*tail)->next = node;
	*tail = (*tail)->next;
	return (1);
}

/* takes a obj_list and as parameter.
allocate a new node then adds the node to the end of the list.
RETURNS: 1 if the node was added correctly, 0 in case of error.
NOTE: if obj is NULL the new node is set as the head of the obj_list.*/
int	ft_lstnew_obj(t_obj_list **obj)
{
	t_obj_list		*node;

	node = (t_obj_list *)malloc(1 * sizeof(t_obj_list));
	if (node == NULL)
		return (0);
	node->next_obj = NULL;
	node->points = NULL;
	if (*obj == NULL)
	{
		*obj = node;
		(*obj)->obj_tail = node;
		return (1);
	}
	(*obj)->obj_tail->next_obj = node;
	(*obj)->obj_tail = (*obj)->obj_tail->next_obj;
	return (1);	
}

/* adds the point to the tail obj */
int	ft_lstadd_obj_tail(t_obj_list *obj_tail, t_point_list **points_tail,
	int color, int value, t_point point)
{
	ft_lstadd_point_tail(&obj_tail->points, points_tail, color, value, point);
	return (1);
}
