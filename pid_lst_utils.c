/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:39:59 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/12 18:39:18 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int				ft_pid_lst_addback_tail(t_pid_lst **list, t_pid_lst **tail,
		t_pid_lst *node);
t_pid_lst		*ft_pthread_lstnew(pthread_t pid);
int				ft_pid_lst_append(t_pid_lst **list, t_pid_lst **tail, int pid);
void			ft_pid_lst_destroy(t_pid_lst **list);
void			ft_print_pid_lst(t_pid_lst *list);

void	ft_print_pid_lst(t_pid_lst *list)
{
	while (list != NULL)
	{
		if (list->obj->tag == DATA)
			ft_printf("DATA: pid=%u\n", list->pid);
		if (list->obj->tag == AXIS)
			ft_printf("AXIS: pid=%u\n", list->pid);
		list = list->next;
	}
}

/* adds the node after the tail pointer passed, then shifts the tail.
RETURNS 0 if the list (double ptr) or the tail (double ptr) passed is null,
1 if all went good. */
int	ft_pid_lst_addback_tail(t_pid_lst **list, t_pid_lst **tail, t_pid_lst *node)
{
	if (!list || !tail)
		return (0);
	if (*list == NULL)
	{
		*list = node;
		*tail = node;
		return (1);
	}
	(*tail)->next = node;
	(*tail) = node;
	return (1);
}

/* create a new node with node->pid equals to the passed pid parameter.
RETURNS: the new allocated node, NULL on malloc failure. */
t_pid_lst	*ft_pthread_lstnew(pthread_t pid)
{
	t_pid_lst	*node;

	node = (t_pid_lst *)malloc(1 * sizeof(t_pid_lst));
	if (!node)
		return (NULL);
	node->pid = pid;
	node->obj = NULL;
	node->mlx = NULL;
	node->next = NULL;
	return (node);
}

/* create a new node with the pid and appens it to the list.
RETURNS 1 if all went good, 0 on error. */
int	ft_pid_lst_append(t_pid_lst **list, t_pid_lst **tail, int pid)
{
	t_pid_lst	*node;

	node = ft_pthread_lstnew(pid);
	if (!node)
		return (0);
	if (ft_pid_lst_addback_tail(list, tail, node) == 0)
		return (0);
	return (1);
}
