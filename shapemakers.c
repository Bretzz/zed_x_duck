/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapemakers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:40:34 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/01 20:22:38 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	fill_area(t_point a, t_point b, t_point c, int color, t_mlx *mlx);
int	fill_line(t_point a, t_point b, int color, t_mlx *mlx);
int	place_axis(float max_z, float max_x, float max_y, t_mlx *mlx);
int	point_to_rombus(t_point p, float value, int color, t_mlx *mlx);

unsigned int blend_colors(unsigned int src, unsigned int dest, unsigned char alpha);

/* takes 3 3D points as parameters and fill the area inbetween them
(appending each element to mlx->live_points, with the color given).
The idea is that a point (p) moves allong a side of the triangle
(never one near an angle grater than 90 degrees), with increments of 1.
At the same time a point (temp_c) moves from the startin point towards the other vertex.
For each increment of the 2 points another point (temp_p)
travels from one (p) to another (temp_c).
The varous values of temp_p are the ones we append to the list.
RETURNS: the number of points added, -1 on error. */
int	fill_area(t_point a, t_point b, t_point c, int color, t_mlx *mlx)
{
	int				ret;
	float			incr[3];
	float			dist[3];
	t_point			p;
	t_point			d;
	t_point			t;
	t_point			temp_p;
	t_point			temp_t;

	/* if (!ft_lstnew_obj(&mlx->live_objs))
		return (-1); */
//	ft_printf("new AREA obj created!\n");
	p = any_not_obtuse(a, b, c);	//point that moves along a side
	d = any_not_obtuse(c, b, a);	//point p move towards
	t = a;							//point that is neither p nor d
	if (point_equal(t, p) || point_equal(t, d))
		t = b;
	if (point_equal(t, p) || point_equal(t, d))
		t = c;
	dist[0] = ft_distf(p, d);
	incr[0] = dist[0] / (1 * dist[0]);
	dist[1] = ft_distf(p, t);
	incr[1] = dist[1] / (1 * dist[1]);
	temp_t = p;
	ret = 0;
	while (dist[1] >= 0.0f)
	{
		temp_p = p;
		dist[2] = ft_distf(temp_p, temp_t);
		incr[2] = dist[2] / (1 * dist[2]);
		while (dist[2] >= 0.0f)
		{
			if (!(ft_lstadd_obj_tail(mlx->live_objs->obj_tail, &mlx->live_objs->points_tail, color, 0, temp_p)))
				return (-1);
			ret++;
//			ft_printf("point %i added!!!\n", ret);
			temp_p.z += incr[2] * ((temp_t.z - temp_p.z) / dist[2]);
			temp_p.x += incr[2] * ((temp_t.x - temp_p.x) / dist[2]);
			temp_p.y += incr[2]* ((temp_t.y - temp_p.y) / dist[2]);
			dist[2] -= incr[2];
		}
		temp_t.z += incr[1] * ((t.z - temp_t.z) / dist[1]);
		temp_t.x += incr[1] * ((t.x - temp_t.x) / dist[1]);
		temp_t.y += incr[1] * ((t.y - temp_t.y) / dist[1]);
		p.z += incr[0] * ((d.z - p.z) / dist[0]);
		p.x += incr[0] * ((d.x - p.x) / dist[0]);
		p.y += incr[0] * ((d.y - p.y) / dist[0]);
		dist[0] -= incr[0];
		dist[1] -= incr[1];
	}
	return (ret);
}

/* takes 2 3D points as parameters.
works just like fill_area() but there's just one point moving from one
of the parameter points to the other.*/
int	fill_line(t_point a, t_point b, int color, t_mlx *mlx)
{
	int		ret;
	float	incr;
	float	dist;

	/* if (!ft_lstnew_obj(&mlx->live_objs))
		return (-1); */
//	ft_printf("new LINE obj created!\n");
	dist = ft_distf(a, b);
	incr = dist / (1 * dist);
	ret = 0;
	while (dist >= 0.0f)
	{
		if (!(ft_lstadd_obj_tail(mlx->live_objs->obj_tail, &mlx->live_objs->points_tail, color, 0, a)))
			return (-1);
		ret++;
		a.z += incr * ((b.z - a.z) / dist);
		a.x += incr * ((b.x - a.x) / dist);
		a.y += incr * ((b.y - a.y) / dist);
		dist -= incr;
	}
	return (ret);
}

/* takes the maximum of each axis and mlx
then adds the points to the live_points list */
int	place_axis(float max_z, float max_x, float max_y, t_mlx *mlx)
{
	int	points;
	t_point	o;
	t_point	z;
	t_point	x;
	t_point	y;
	
	to_zero(&o);
	if (!ft_lstnew_obj(&mlx->live_objs))
		return (-1);
	mlx->live_objs->obj_tail->origin = o;
	mlx->live_objs->obj_tail->tag = AXIS;
	points = 0;
	to_zero(&z);
	to_zero(&x);
	to_zero(&y);
	y.y = max_y;
	points += fill_line(o, y, 0xFFFFFF, mlx);
	z.z = max_z;
	x.x = max_x;
	z.y = max_y;
	x.y = max_y;
	o.y = max_y;
	points += fill_line(o, z, 0xFFFFFF, mlx);
	points += fill_line(o, x, 0xFFFFFF, mlx);
	return (points);
}

/* ty chatgpt :D */
unsigned int blend_colors(unsigned int src, unsigned int dest, unsigned char alpha)
{
    // Extract RGB components from source color
    unsigned char src_r = (src >> 16) & 0xFF;
    unsigned char src_g = (src >> 8) & 0xFF;
    unsigned char src_b = src & 0xFF;

    // Extract RGB components from destination color (background)
    unsigned char dest_r = (dest >> 16) & 0xFF;
    unsigned char dest_g = (dest >> 8) & 0xFF;
    unsigned char dest_b = dest & 0xFF;

    // Blend each color component using the alpha value
    unsigned char r = (src_r * alpha + dest_r * (255 - alpha)) / 255;
    unsigned char g = (src_g * alpha + dest_g * (255 - alpha)) / 255;
    unsigned char b = (src_b * alpha + dest_b * (255 - alpha)) / 255;

    // Reassemble the blended color
    return (r << 16) | (g << 8) | b;
}

/* take a point, an int and mlx as parameters.
takes all the 6 points obtained by increasing or decreasing
individually each coordinate of the point by the int passed as parameter.
then fills al the areas forming the prysm.
RETURNS: the number of points forming the areas.*/
int	point_to_rombus(t_point p, float value, int color , t_mlx *mlx)
{
	int				i;
	t_point 		vertex[6];

	if (!ft_lstnew_obj(&mlx->live_objs))
		return (-1);
	mlx->live_objs->obj_tail->origin = p;
	mlx->live_objs->obj_tail->tag = DATA;
	i = 0;
	while (i < 6)
	{
		vertex[i] = p;
		i++;
	}
	vertex[0].z += value;
	vertex[1].z -= value;
	vertex[2].x += value;
	vertex[3].x -= value;
	vertex[4].y += value;
	vertex[5].y -= value;
	/* if (value <= 4.0f)
		color = blend_colors(color, 0x000000, 128); */
	i = 0;
	i += fill_area(vertex[5], vertex[2], vertex[0], color, mlx);
	i += fill_area(vertex[5], vertex[2], vertex[1], color, mlx);
	i += fill_area(vertex[5], vertex[3], vertex[0], color, mlx);
	i += fill_area(vertex[5], vertex[3], vertex[1], color, mlx);
	color += 10000;
	i += fill_area(vertex[4], vertex[2], vertex[0], color, mlx);
	i += fill_area(vertex[4], vertex[2], vertex[1], color, mlx);
	i += fill_area(vertex[4], vertex[3], vertex[0], color, mlx);
	i += fill_area(vertex[4], vertex[3], vertex[1], color, mlx);
	/* i += fill_area(vertex[0], vertex[2], vertex[5], 0xFF00Fc, mlx);
	i += fill_area(vertex[0], vertex[2], vertex[4], 0x2FFFA2, mlx);
	i += fill_area(vertex[0], vertex[3], vertex[5], 0x00a2FF, mlx);
	i += fill_area(vertex[0], vertex[3], vertex[4], 0x00FFFF, mlx);
	i += fill_area(vertex[1], vertex[2], vertex[5], 0xFF0F01, mlx);
	i += fill_area(vertex[1], vertex[2], vertex[4], 0xcdcd01, mlx);
	i += fill_area(vertex[1], vertex[3], vertex[5], 0x0000FF, mlx);
	i += fill_area(vertex[1], vertex[3], vertex[4], 0xD6108F, mlx); */
	return (i);
}
