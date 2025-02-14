/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_masters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:56:34 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/13 16:24:53 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	put_point(t_point p, int color, t_mlx *mlx);
t_point	rotate_point(t_point p, t_point c, t_mlx *mlx);
t_point	get_centre(t_point *data, int pt_num);
t_point	get_list_centre(t_point_list *data, int pt_num);

t_point	zed_norm(t_point p);
t_point	fdf_norm(t_point p, t_mlx *mlx);

/* resizing based on map size and screen size. */
t_point	fdf_norm(t_point p, t_mlx *mlx)
{
	t_point	norm_p;

	(void)mlx;
	//ft_printf("x-ratio=%u\n", (mlx->win_x - 100) / mlx->data.max_x);
	/* ft_ *///printf("z-ratio=%f\n", 100 / mlx->data.max_z);
	norm_p.x = p.x * ((mlx->win_x - 100) / mlx->data.max_x);
	norm_p.y = p.y * ((mlx->win_y - 100) / mlx->data.max_y);
	float z_range = (p.z - mlx->data.min_z) / (mlx->data.max_z - mlx->data.min_z);
    norm_p.z = (log(1 + z_range) * (mlx->win_y / 10)) * -1;	
	//norm_p.z = ((p.z - 0) * ((50) / mlx->data.max_z)) * -1;
	return (norm_p);
}

/* this function does the magic.
if you pass a (1, 1, 1), it returns the equivalent in the axis we just plot
(actually just swaps the y coordinate :D) */
// VOLUME -- Xmin: 6000 -- Xmax: 6800
// VOLUME -- Ymin: 2800 -- Ymax: 4000
// VOLUME -- Zmin: -1400 -- Zmax: -800
t_point	zed_norm(t_point p)
{
	t_point	norm_p;

	//norm_p.x = ((p.x - 6000) / 800) * mlx->win_x - 100;
	norm_p.x = (p.x - 6000);
	norm_p.y = (p.y + 1400) * -1;
	norm_p.z = p.z - 2800;
	return (norm_p);
}

/* Takes a t_point as a parameter and plots it to the image */
void	put_point(t_point p, int color, t_mlx *mlx)
{
	float		x;
	float		y;
	float		z;
	t_point	plot;
	
	plot = rotate_point(p, mlx->data.centre, mlx);
	
	//printf("new-zoom-x=%f, new-zoom-y=%f\n", mlx->plane.zoom_x, mlx->plane.zoom_y);
	x = (plot.x + mlx->plane.origin.x + mlx->plane.x_shift) * mlx->plane.scale;
	y = (plot.y + mlx->plane.origin.y + mlx->plane.y_shift) * mlx->plane.scale;
	z = mlx->plane.origin.z + plot.z;
	
	// If the point is off-screen, do not draw it
	if (x < 0 || y < 0 || /* z > 0 || */ x >= mlx->win_x || y >= mlx->win_y)
		return ;
	/* if (x > 1400.8f)
		printf("putting (%f, %f, %f)\n", x, y, z); */
	my_pixel_put(mlx, (int)x, (int)y, z, color);
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

	centre.x = 0;
	centre.y = 0;
	centre.z = 0;

	i = 0;
	while (i < pt_num)
	{
		centre.x += data[i].x;
		centre.y += data[i].y;
		centre.z += data[i].z;
		i++;
	}
	centre.x /= pt_num;
	centre.y /= pt_num;
	centre.z /= pt_num;
	return (centre);
}

/* just as get_centre() but with lists :D */
t_point	get_list_centre(t_point_list *data, int pt_num)
{
	int		i;
	t_point	centre;

	centre.x = 0;
	centre.y = 0;
	centre.z = 0;

	i = 0;
	while (data && i < pt_num)
	{
		centre.x += data->point.x;
		centre.y += data->point.y;
		centre.z += data->point.z;
		data = data->next;
		i++;
	}
	centre.x /= pt_num;
	centre.y /= pt_num;
	centre.z /= pt_num;
	return (centre);
}
