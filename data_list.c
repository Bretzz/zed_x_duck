/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:32:19 by totommi           #+#    #+#             */
/*   Updated: 2025/02/18 03:31:22 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	    ft_datalst_add_tail(t_data_list **list, t_data_list **tail,
			void *values, t_point point);
t_point	get_data_list_centre(t_data_list *list, int pt_num);
void	ft_free_data_list(t_data_list *list, void (*del)(void *));

/* takes a data_list head and tail, a point and it's values as parameters.
allocate a new node with the data of the point,
then adds the node to the end of the list.
RETURNS: 1 if the node was added correctly, 0 in case of error.
NOTE: if list is NULL the new node is set as the head of the list. 
NOTE: values is expected to be a freeable poitner. */
int	ft_datalst_add_tail(t_data_list **list, t_data_list **tail,
	void *values, t_point point)
{
	t_data_list	*node;

	node = (t_data_list *)malloc(1 * sizeof(t_data_list));
	if (node == NULL)
		return (0);
	node->point = point;
	node->values = values;
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

/* just as get_centre() but with lists :D */
t_point	get_data_list_centre(t_data_list *list, int pt_num)
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

void	ft_free_data_list(t_data_list *list, void (*del)(void *))
{
    t_data_list *prev;

	(void)del;
	while (list != NULL)
    {
        prev = list;
        list = list->next;
        //(*del)(prev->values); //segfaults on duck_free_obj_list
        free(prev);
    }
}
