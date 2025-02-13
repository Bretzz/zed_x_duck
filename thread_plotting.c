/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_plotting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:09:10 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/12 15:49:47 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	*put_layer_thread(void *arg);
void	put_data_thread(t_mlx *mlx);
void	mass_join(t_pid_lst *list);

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
		put_obj(obj, p_list->mlx);
		obj = obj->next_obj;
		i++;
	}
	return (NULL);
}

void	put_data_thread(t_mlx *mlx)
{
	t_obj_list		*obj;
	t_pid_lst	*p_list;
	t_pid_lst	*p_tail;
	int			i;
	unsigned int	thread_ratio;
	//int			threads;

	p_list = NULL;
	obj = mlx->live_objs;
	//threads = 0;
	i = 0;
	//ft_printf("%u\n", mlx->data.obj_nb);
	thread_ratio = mlx->data.obj_nb / MAX_THREADS;
	while (obj != NULL)
	{
		if (mlx->data.obj_nb < MAX_THREADS
			|| i % thread_ratio == 0)
		{
			//threads++;
			ft_pid_lst_append(&p_list, &p_tail, (pthread_t)0);
			p_tail->obj = obj;
			p_tail->mlx = mlx;
			p_tail->layer = thread_ratio;
			if (pthread_create(&p_tail->pid, NULL,
					&put_layer_thread, p_tail) < 0)
				return ;
		}
		obj = obj->next_obj;
		i++;
	}
	mass_join(p_list);
	ft_free_pid_lst(&p_list);
	//ft_printf("%i thread used\n", threads);
}
