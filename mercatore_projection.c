/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mercatore_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:41:06 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/13 11:39:59 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	merca_obj_list(t_obj_list *list, size_t radius, int max_x, int max_y);

t_point	geographic_to_cartesian(float lat, float lon, size_t radius)
{
	t_point cart_p;

	cart_p.x = radius * cosf(lat) * cosf(lon);
	cart_p.y = radius * cosf(lat) * sinf(lon);
	cart_p.z = radius * sinf(lat);
	
	return (cart_p);
}

/* applies the mercatore_projection to the given point. */
t_point	mercatore_projection(t_point p, size_t radius, int max_x, int max_y)
{
	float	lat;
	float	lon;
	//float	z-offset;
	t_point	ret_p;

	lat = (2 * atanf(expf(-(MY_PI / 2 ) + (p.y / max_y) * MY_PI))) - MY_PI / 2; // for Mercator's y (latitude)
	lon = -MY_PI + (p.x / max_x) * (2 * MY_PI);
	//z-offset = 0;
	/* if (i % 10000 == 0)
		printf("Latitude: %f, Longitude: %f\n", lat, lon);
	i++; */
	ret_p = geographic_to_cartesian(lat, lon, radius + (p.z * -1));
	return (ret_p);
}

/* takes an obj array as parameter.
Apply the mercatore_projection() to every point of the objs. */
int	merca_obj_list(t_obj_list *obj_list, size_t radius, int max_x, int max_y)
{
	t_point_list	*list;

	while (obj_list != NULL)
	{
		list = obj_list->points;
		while (list != NULL)
		{
			list->point = mercatore_projection(list->point, radius, max_x, max_y);
			list = list->next;
		}
		obj_list = obj_list->next_obj;
	}
	return (1);
}

