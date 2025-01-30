/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:16:00 by totommi           #+#    #+#             */
/*   Updated: 2025/01/29 02:17:28 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

float	ft_anglef(t_point a, t_point o, t_point b);
float	ft_areaf(t_point a, t_point b, t_point c);
int	    is_inside(t_point p, t_point a, t_point b, t_point c);

/* returns te angle formed by 3 3D points, OA^OB */
float	ft_anglef(t_point a, t_point o, t_point b)
{
	return (acosf((((a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y) + (a.z - o.z) * (b.z - o.z))
		/ (sqrtf((a.x - o.x) * (a.x - o.x) + (a.y - o.y) * (a.y - o.y) + (a.z - o.z) * (a.z - o.z))
		* sqrtf((b.x - o.x) * (b.x - o.x) + (b.y - o.y) * (b.y - o.y) + (b.z - o.z) * (b.z - o.z))))));
}

/* ab x ac = modulo(ab) * modulo(ac) * cos(theta) */
float	ft_areaf(t_point a, t_point b, t_point c)
{
	return ((ft_distf(a, b) * ft_distf(a, c) * sinf(ft_anglef(b, a, c)) / 2.0f));
}

//https://math.stackexchange.com/questions/4322/check-whether-a-point-is-within-a-3d-triangle
/* takes 4 3D space points as parameters.
checks wether the first one is contained in the triangle
fromed by the other 3.
RETURNS: 1 if it's contained, 0 if it isn't. */
int	is_inside(t_point p, t_point a, t_point b, t_point c)
{
	float	area;
	float	alpha;
	float	beta;
	float	gamma;

	area = ft_areaf(a, b, c);
	alpha = ft_areaf(p, b, c);
	beta = ft_areaf(p, a, c);
	gamma = ft_areaf(p, b, a);
	if (alpha + beta + gamma == area)
		return (1);
	/* alpha = ft_areaf(p, b, c) / area;
	beta = ft_areaf(p, c, a) / area;
	gamma = 1 - alpha - beta;
	if (alpha + beta + gamma == 1
		&& (alpha >=0 && beta >= 0 && gamma >= 0)
		&& (alpha == 1 || beta == 1 || gamma == 1))
		{
			printf("RET(3): aalpha=%f, beta=%f, gamma=%f\n", alpha, beta, gamma);
			return (3);
		}
	if ((alpha >= 0 && alpha <= 1)
		&& (beta >= 0 && beta <= 1)
		&& (gamma >= 0 && gamma <= 1)
		&& alpha + beta + gamma == 1.0f)
		{
			printf("RET(1): alpha=%f, beta=%f, gamma=%f\n", alpha, beta, gamma);
			return (1);
		} */
	return (0);
}