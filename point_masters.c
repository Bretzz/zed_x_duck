/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_masters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:56:34 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/01 20:44:47 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	put_point(t_point p, int color, t_mlx *mlx);
t_point	rotate_point(t_point p, t_point c, t_mlx *mlx);
t_point	get_centre(t_point *data, int pt_num);
t_point	get_list_centre(t_point_list *data, int pt_num);

/* Takes a t_point as a parameter and plots it to the image */
void	put_point(t_point p, int color, t_mlx *mlx)
{
	float	z;
	int		x;
	int		y;
	t_point	plot;
	
	plot = p;
	
	// Apply the projection and translation to screen coordinates
	z = mlx->plane.origin.z + plot.z;
	x = mlx->plane.origin.x + plot.x;
	y = mlx->plane.origin.y + plot.y + mlx->plane.y_shift;
	
	// If the point is off-screen, do not draw it
	if (x < 0 || y < 0 || /* z > 0 || */ x >= mlx->win_x || y >= mlx->win_y)
		return ;
	my_pixel_put(mlx, x, y, z, color);
}


/* takes a point and a t_mlx struct as parameter
The function rotate the point based on the angles.
mlx_plane->r_* are the angle we want to rotate each point,
and we are rotating the point around c.
RETURNS: the rotated point.*/
t_point	rotate_point(t_point p, t_point c, t_mlx *mlx)
{
	float	temp_x;
	float	temp_y;
	t_point	new_point;

	new_point = p;
	new_point.z -= c.z;
	new_point.x -= c.x;
	new_point.y -= c.y;
	
	// Apply rotation around the X-axis
	temp_y = new_point.y;
	new_point.y = new_point.y * cos(mlx->plane.r_x) - new_point.z * sin(mlx->plane.r_x);
	new_point.z = temp_y * sin(mlx->plane.r_x) + new_point.z * cos(mlx->plane.r_x);

	// Apply rotation around the Y-axis
	temp_x = new_point.x;
	new_point.x = new_point.x * cos(mlx->plane.r_y) + new_point.z * sin(mlx->plane.r_y);
	new_point.z = -temp_x * sin(mlx->plane.r_y) + new_point.z * cos(mlx->plane.r_y);

	// Apply rotation around the Z-axis
    temp_x = new_point.x;
    new_point.x = new_point.x * cos(mlx->plane.r_z) - new_point.y * sin(mlx->plane.r_z);
    new_point.y = temp_x * sin(mlx->plane.r_z) + new_point.y * cos(mlx->plane.r_z);

	// Translate the object so that its center is at the origin
	new_point.z += c.z;
	new_point.x += c.x;
	new_point.y += c.y;
	return (new_point);
}

/* takes an array of points and RETURNS the coordinates of the centre */
t_point	get_centre(t_point *data, int pt_num)
{
	int		i;
	t_point	centre;

	centre.z = 0;
	centre.x = 0;
	centre.y = 0;

	i = 0;
	while (i < pt_num)
	{
		centre.z += data[i].z;
		centre.x += data[i].x;
		centre.y += data[i].y;
		i++;
	}
	centre.z /= pt_num;
	centre.x /= pt_num;
	centre.y /= pt_num;
	return (centre);
}

/* just as get_centre() but with lists :D */
t_point	get_list_centre(t_point_list *data, int pt_num)
{
	int		i;
	t_point	centre;

	centre.z = 0;
	centre.x = 0;
	centre.y = 0;

	i = 0;
	while (data && i < pt_num)
	{
		centre.z += data->point.z;
		centre.x += data->point.x;
		centre.y += data->point.y;
		data = data->next;
		i++;
	}
	centre.z /= pt_num;
	centre.x /= pt_num;
	centre.y /= pt_num;
	return (centre);
}
