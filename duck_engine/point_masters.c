/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_masters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:56:34 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/14 22:36:56 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duck_engine.h"

#include <stdio.h>

void	put_point(t_point p, int color, void (*pixel_put)(void *, int, int, float, unsigned int), t_duck *duck);
t_point	rotate_point(t_point p, t_point c, t_duck *duck);

//void	my_pixel_put(t_mlx *mlx, int x, int y, float z, int color);
/* Takes a t_point as a parameter and plots it to the image */
void	put_point(t_point p, int color, void (*pixel_put)(void *, int, int, float, unsigned int), t_duck *duck)
{
	float		x;
	float		y;
	float		z;
	t_point	plot;
	
	plot = rotate_point(p, duck->centre, duck);
	x = (plot.x + duck->plane.xoffset) * duck->plane.scale;
	y = (plot.y + duck->plane.yoffset) * duck->plane.scale;
	z = plot.z;
	(*pixel_put)(duck->mlx, (int)x, (int)y, z, color);
}

/* takes a point and a t_duck struct as parameter
The function rotate the point based on the angles.
duck_plane->r_* are the angle we want to rotate each point,
and we are rotating the point around c.
RETURNS: the rotated point.*/
t_point	rotate_point(t_point p, t_point c, t_duck *duck)
{
	float	temp_x;
	float	temp_y;
	t_point	new_point;

	new_point = p;
	new_point.x -= c.x;
	new_point.y -= c.y;
	new_point.z -= c.z;

	// Apply rotation around the X-axis
	temp_y = new_point.y;
	new_point.y = new_point.y * cos(duck->plane.r_x) - new_point.z * sin(duck->plane.r_x);
	new_point.z = temp_y * sin(duck->plane.r_x) + new_point.z * cos(duck->plane.r_x);

	// Apply rotation around the Y-axis
	temp_x = new_point.x;
	new_point.x = new_point.x * cos(duck->plane.r_y) + new_point.z * sin(duck->plane.r_y);
	new_point.z = -temp_x * sin(duck->plane.r_y) + new_point.z * cos(duck->plane.r_y);

	// Apply rotation around the Z-axis
    temp_x = new_point.x;
    new_point.x = new_point.x * cos(duck->plane.r_z) - new_point.y * sin(duck->plane.r_z);
    new_point.y = temp_x * sin(duck->plane.r_z) + new_point.y * cos(duck->plane.r_z);

	// Translate the object so that its center is at the origin
	new_point.z += c.z;
	new_point.x += c.x;
	new_point.y += c.y;
	return (new_point);
}
