/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_plotting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:09:10 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/18 01:46:21 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duck_engine.h"

void	put_data_thread(t_duck *duck, int (*exclude)(void *, t_obj_list *), void (*pixel_put)(void *, int, int, float, unsigned int));

void	mass_join(t_pid_lst *list)
{
	while (list != NULL)
	{
		pthread_join(list->pid, NULL);
		list = list->next;
	}
}

void	*put_layer_thread(void *arg)
{
	t_pid_lst		*p_list;
	t_obj_list		*obj;
	unsigned int	i;

	p_list = (t_pid_lst *)arg;
	obj = p_list->obj;
	i = 0;
	while (i <= p_list->layer && obj != NULL)
	{
		put_obj(obj, p_list->duck, p_list->exclude, p_list->pixel_put);
		obj = obj->next_obj;
		i++;
	}
	return (NULL);
}

void	put_data_thread(t_duck *duck, int (*exclude)(void *, t_obj_list *), void (*pixel_put)(void *, int, int, float, unsigned int))
{
	t_obj_list	*obj;
	t_pid_lst	*p_list;
	t_pid_lst	*p_tail;
	int			i;
	unsigned int	thread_ratio;

	p_list = NULL;
	obj = duck->live_objs;
	i = 0;
	thread_ratio = duck->obj_nb / MAX_THREADS;
	while (obj != NULL)
	{
		if (duck->obj_nb < MAX_THREADS
			|| i % thread_ratio == 0)
		{
			duck_pidnew_tail(&p_list, &p_tail, (pthread_t)0);
			p_tail->obj = obj;
			p_tail->duck = duck;
			p_tail->layer = thread_ratio;
			p_tail->pixel_put = pixel_put;
			p_tail->exclude = exclude;
			if (pthread_create(&p_tail->pid, NULL,
					&put_layer_thread, p_tail) < 0)
				return ;
		}
		obj = obj->next_obj;
		i++;
	}
	mass_join(p_list);
	duck_free_pid_lst(&p_list);
}
