/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_plotting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:29:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/14 23:16:45 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duck_engine.h"

void	put_obj(t_obj_list *obj, t_duck *duck, int (*exclude)(void *, t_obj_list *), void (*pixel_put)(void *, int, int, float, unsigned int));
void	put_data(t_duck *duck, int (*exclude)(void *, t_obj_list *), void (*pixel_put)(void *, int, int, float, unsigned int));

/* 
if ((obj->tag == DATA && ((mlx->setty.sel_y <= 0 && (obj->origin.y == mlx->setty.sel_y))
		|| (mlx->setty.sel_x > 0 && mlx->setty.sel_y > 0 && mlx->setty.sel_z > 0))
		&& (mlx->setty.mana <= 0 || obj->obj_value > mlx->setty.mana))
		|| obj->tag != DATA)
	{
*/

void	put_obj(t_obj_list *obj, t_duck *duck, int (*exclude)(void *, t_obj_list *), void (*pixel_put)(void *, int, int, float, unsigned int))
{
	t_point_list	*list;

	list = obj->points;
	while (list != NULL)
	{
		if (!(*exclude)(duck->mlx, obj))
			put_point(list->point, list->color, pixel_put, duck);
		list = list->next;
	}
}

void	put_data(t_duck *duck, int (*exclude)(void *, t_obj_list *), void (*pixel_put)(void *, int, int, float, unsigned int))
{
	t_obj_list		*obj;

	obj = duck->live_objs;
	while (obj != NULL)
	{
		put_obj(obj, duck, exclude, pixel_put);
		obj = obj->next_obj;
	}
}
