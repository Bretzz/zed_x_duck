/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:32:19 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/18 03:07:46 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duck_engine.h"

/* ! ! ! IMPORTANT ! ! ! */
/* The void * passed to point_to_obj_tail must be either a float * or
a struct * with a float as variable entry, either wey we encounter an
unexpected behaviour. */

int		duck_objnew(t_obj_list **obj);
int		duck_pointail(t_point_list **list, int color, float data, t_point point);
int		duck_point_to_obj_tail(t_obj_list *obj_tail, int color, void *data, t_point point);
t_point	get_list_centre(t_point_list *list, int pt_num);

/* takes a obj_list and as parameter.
allocate a new node then adds the node to the end of the list.
RETURNS: 1 if the node was added correctly, 0 in case of error.
NOTE: if obj is NULL the new node is set as the head of the obj_list.*/
int	duck_objnew(t_obj_list **obj)
{
	t_obj_list		*node;

	node = (t_obj_list *)malloc(1 * sizeof(t_obj_list));
	if (node == NULL)
		return (0);
	node->data = NULL;
	node->points = NULL;
	node->next_obj = NULL;
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

/* takes a point_list and a point as parameters.
allocate a new node with the data of the point,
then adds the node to the end of the list.
RETURNS: 1 if the node was added correctly, 0 in case of error.
NOTE: if list is NULL the new node is set as the head of the list.*/
int	duck_pointail(t_point_list **list, int color, float data, t_point point)
{
	t_point_list	*node;

	node = (t_point_list *)malloc(1 * sizeof(t_point_list));
	if (node == NULL)
		return (0);
	node->point = point;
	node->data = data;
	node->color = color;
	node->next = NULL;
	if (*list == NULL)
	{
		*list = node;
		(*list)->tail = node;
		return (1);
	}
	(*list)->tail->next = node;
	(*list)->tail = (*list)->tail->next;
	return (1);
}

/* adds the point to the tail obj */
int	duck_point_to_obj_tail(t_obj_list *obj_tail, int color, void *data, t_point point)
{
	float value;

	if (data != NULL)
		value = *(float *)data;
	else
		value = 0.0f;
	duck_pointail(&obj_tail->points, color, value, point);
	return (1);
}
/* just as get_centre() but with lists :D */
t_point	get_list_centre(t_point_list *list, int pt_num)
{
	int		i;
	t_point	centre;

	centre.x = 0;
	centre.y = 0;
	centre.z = 0;

	i = 0;
	while (list && i < pt_num)
	{
		centre.x += list->point.x;
		centre.y += list->point.y;
		centre.z += list->point.z;
		list = list->next;
		i++;
	}
	centre.x /= pt_num;
	centre.y /= pt_num;
	centre.z /= pt_num;
	return (centre);
}
