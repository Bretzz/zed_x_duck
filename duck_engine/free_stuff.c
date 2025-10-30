/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:26:33 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/18 03:38:38 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duck_engine.h"

void	ft_free_arr(char **arr);
void	duck_free_point_list(t_point_list *list);
void	duck_free_obj_list(t_obj_list *obj, void (*del)(void *));
void	duck_free_pid_lst(t_pid_lst **list);

void	ft_free_arr(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	duck_free_point_list(t_point_list *list)
{
	t_point_list	*prev;

	while (list != NULL)
	{
		prev = list;
		list = list->next;
		free(prev);
	}
}

void	duck_free_obj_list(t_obj_list *obj, void (*del)(void *))
{
	t_obj_list	*prev;

	while (obj != NULL)
	{
		prev = obj;
		obj = obj->next_obj;
		(*del)(prev->data);
		duck_free_point_list(prev->points);
		free(prev);
	}
}


void	duck_free_pid_lst(t_pid_lst **list)
{
	t_pid_lst	*curr;
	t_pid_lst	*prev;

	if (!list)
		return ;
	curr = *list;
	while (curr != NULL)
	{
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	*list = NULL;
}
