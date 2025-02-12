/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checky_funtions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:26:33 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/12 18:55:43 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	ft_free_arr(char **arr);
void	ft_free_point_list(t_point_list *list);
void	ft_free_obj_list(t_obj_list *obj);
void	ft_free_pid_lst(t_pid_lst **list);

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

void	ft_free_point_list(t_point_list *list)
{
	t_point_list	*prev;

	while (list != NULL)
	{
		prev = list;
		list = list->next;
		free(prev);
	}
}

void	ft_free_obj_list(t_obj_list *obj)
{
	t_obj_list	*prev;

	while (obj != NULL)
	{
		prev = obj;
		obj = obj->next_obj;
		ft_free_point_list(prev->points);
		free(prev);
	}
}


void	ft_free_pid_lst(t_pid_lst **list)
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
