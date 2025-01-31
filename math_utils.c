/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:11:16 by totommi           #+#    #+#             */
/*   Updated: 2025/01/31 15:53:41 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	    point_equal(t_point a, t_point b);
t_point	any_not_obtuse(t_point a, t_point b, t_point c);
float	ft_distf(t_point a, t_point b);
float	ft_absf(float f);

t_point	*to_zero(t_point *p);
t_point	*to_one(t_point *p);

t_point	major_z(t_point a, t_point b);
t_point	major_x(t_point a, t_point b);
t_point	major_y(t_point a, t_point b);
t_point	minor_z(t_point a, t_point b);
t_point	minor_x(t_point a, t_point b);
t_point	minor_y(t_point a, t_point b);

/* checks wether 2 points are equal */
int	point_equal(t_point a, t_point b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (1);
	return (0);
}

/* takes 3 points as parameters.
returns the first angle found not grater than 90 degrees. */
t_point	any_not_obtuse(t_point a, t_point b, t_point c)
{
	if (ft_anglef(b, a, c) < MY_PI / 2)
		return (a);
	if (ft_anglef(a, b, c) < MY_PI / 2)
		return (b);
	else
		return (c);
}

/* takes 2 3D points as parameters.
returns the distance (float) between them. */
float	ft_distf(t_point a, t_point b)
{
	return (sqrtf(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)) + ((a.z - b.z) * (a.z - b.z))));
}

/* returs the absolute value (float) of the number passed */
float	ft_absf(float f)
{
	if (f < 0)
		return (f * -1.0f);
	return (f);
}

/* sets a point's cordinate to zero */
t_point	*to_zero(t_point *p)
{
	p->z = 0.0f;
	p->x = 0.0f;
	p->y = 0.0f;
	return (p);
}

/* sets a point's cordinate to one */
t_point	*to_one(t_point *p)
{
	p->z = 1;
	p->x = 1;
	p->y = 1;
	return (p);
}

/* takes 2 points as paraemters,
returns the one with smaller value on the z axis */
t_point	minor_z(t_point a, t_point b)
{
	if(a.z < b.z)
		return (a);
	return (b);
}

/* takes 2 points as paraemters,
returns the one with smaller value on the x axis */
t_point	minor_x(t_point a, t_point b)
{
	if(a.x < b.x)
		return (a);
	return (b);
}

/* takes 2 points as paraemters,
returns the one with smaller value on the y axis */
t_point	minor_y(t_point a, t_point b)
{
	if(a.y < b.y)
		return (a);
	return (b);
}

/* takes 2 points as paraemters,
returns the one with grater value on the z axis */
t_point	major_z(t_point a, t_point b)
{
	if(a.z > b.z)
		return (a);
	return (b);
}

/* takes 2 points as paraemters,
returns the one with grater value on the x axis */
t_point	major_x(t_point a, t_point b)
{
	if(a.x > b.x)
		return (a);
	return (b);
}

/* takes 2 points as paraemters,
returns the one with grater value on the y axis */
t_point	major_y(t_point a, t_point b)
{
	if(a.y > b.y)
		return (a);
	return (b);
}
