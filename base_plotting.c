/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_plotting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:29:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/12 18:30:24 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	put_obj(t_obj_list *obj, t_mlx *mlx);
void	put_data(t_mlx *mlx);

void	put_obj(t_obj_list *obj, t_mlx *mlx)
{
	t_point_list	*list;
	
	if ((obj->tag == DATA && ((mlx->setty.sel_y <= 0 && (obj->origin.y == mlx->setty.sel_y))
		|| (mlx->setty.sel_x > 0 && mlx->setty.sel_y > 0 && mlx->setty.sel_z > 0))
		&& (mlx->setty.mana <= 0 || obj->obj_value > mlx->setty.mana))
		|| obj->tag != DATA)
	{
		list = obj->points;
		while (list != NULL)
		{
			put_point(list->point, list->color, mlx);
			list = list->next;
		}
	}
}

void	put_data(t_mlx *mlx)
{
	t_obj_list		*obj;

	obj = mlx->live_objs;
	while (obj != NULL)
	{
		put_obj(obj, mlx);
		obj = obj->next_obj;
	}
}
