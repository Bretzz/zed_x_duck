/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:39:59 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/18 01:30:27 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duck_engine.h"

t_pid_lst	*duck_pidnew(pthread_t pid);
int			duck_pid_tail(t_pid_lst **list, t_pid_lst **tail, t_pid_lst *node);
int			duck_pidnew_tail(t_pid_lst **list, t_pid_lst **tail, pthread_t pid);

/* create a new node with node->pid equals to the passed pid parameter.
RETURNS: the new allocated node, NULL on malloc failure. */
t_pid_lst	*duck_pidnew(pthread_t pid)
{
	t_pid_lst	*node;

	node = (t_pid_lst *)malloc(1 * sizeof(t_pid_lst));
	if (!node)
		return (NULL);
	node->pid = pid;
	node->obj = NULL;
	node->duck = NULL;
	node->next = NULL;
	return (node);
}

/* adds the node after the tail pointer passed, then shifts the tail.
RETURNS 0 if the list (double ptr) or the tail (double ptr) passed is null,
1 if all went good. */
int	duck_pid_tail(t_pid_lst **list, t_pid_lst **tail, t_pid_lst *node)
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

/* create a new node with the pid and appens it to the list.
RETURNS 1 if all went good, 0 on error. */
int	duck_pidnew_tail(t_pid_lst **list, t_pid_lst **tail, pthread_t pid)
{
	t_pid_lst	*node;

	node = duck_pidnew(pid);
	if (!node)
		return (0);
	if (duck_pid_tail(list, tail, node) == 0)
		return (0);
	return (1);
}
