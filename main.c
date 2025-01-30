/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:54:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/30 09:16:41 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	my_pixel_put(t_mlx *mlx, int x, int y, float z, int color);
void	put_point(t_point p, int color, t_mlx *mlx);
void	plot_data(t_mlx *mlx);

/* we shoould take into accounnt the depth of the point,
but we're not handling black points priority. */
void	my_pixel_put(t_mlx *mlx, int x, int y, float z, int color)
{
	char	*dst;
	float	*z_dest;
	
	dst = mlx->img->addr + (y * mlx->img->line_length + x * (mlx->img->bits_per_pixel / sizeof(int *)));
	z_dest = mlx->z_img + (y * mlx->img->line_length + x * (mlx->img->bits_per_pixel / sizeof(float *)));
	/* if (*dst != 0x0 && *z_dest < z)
		return ; */
	*(unsigned int *)dst = color;
	*(float *)z_dest = z;
}

/* takes an array of points and returns the coordinates of the centre */
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

/* takes 3 2D points as parameters and fill the area inbetween them */
void	fill_area(t_point a, t_point b, t_point c, t_mlx *mlx)
{
	int		ret;
	float	incr[3];
	float	dist[3];
	t_point	p;
	t_point	d;
	t_point	t;
	t_point	temp_p;
	t_point	temp_t;
	t_point_list	*tail;

	if (mlx->live_points == NULL)
		tail = NULL;
	else
	{
		tail = mlx->live_points;
		while (tail && tail->next)
			tail = tail->next;
	}
	
	p = any_not_obtuse(a, b, c); //point that moves along a side
	d = any_not_obtuse(c, b, a); //point to move towards
	t = a; //point that is neither p nor d
	if (point_equal(t, p) || point_equal(t, d))
		t = b;
	if (point_equal(t, p) || point_equal(t, d))
		t = c;
	dist[0] = ft_distf(p, d);
	incr[0] = dist[0] / 100;
	dist[1] = ft_distf(p, t);
	incr[1] = dist[1] / 100;
	temp_t = p;
	ret = 0;
	while (dist[1] > 1.0f)
	{
		temp_p = p;
		dist[2] = ft_distf(temp_p, temp_t);
		incr[2] = dist[2] / 100;
		while (dist[2] > 1.0f)
		{
			//ft_printf("gatto????\n");
//			printf("dist3=%f\n", dist3);
//			printf("temp_p = (%f, %f, %f)\n", temp_p.x, temp_p.y, temp_p.z);
			ft_lstadd_point_tail(&mlx->live_points, &tail, temp_p);
				//ft_printf("Error\n");	//PROTECT TE MALLOCC!!!
		//	put_point(temp_p, color, mlx);
			ret++;
//			ft_printf("micio????\n");
			temp_p.z += incr[2] * ((temp_t.z - temp_p.z) / dist[2]);
			temp_p.x += incr[2] * ((temp_t.x - temp_p.x) / dist[2]);
			temp_p.y += incr[2]* ((temp_t.y - temp_p.y) / dist[2]);
//			ft_printf("miaooooo!!!\n");
			dist[2] -= incr[2];
//			ft_printf("sacco?\n");
		}
//		printf("dist2=%f\n", dist2);
//		printf("p = (%f, %f, %f)\n", p.x, p.y, p.z);
//		printf("temp_t = (%f, %f, %f)\n", temp_t.x, temp_t.y, temp_t.z);
//		ft_printf("gatto?\n");
		temp_t.z += incr[1] * ((t.z - temp_t.z) / dist[1]);
		temp_t.x += incr[1] * ((t.x - temp_t.x) / dist[1]);
		temp_t.y += incr[1] * ((t.y - temp_t.y) / dist[1]);
		p.z += incr[0] * ((d.z - p.z) / dist[0]);
		p.x += incr[0] * ((d.x - p.x) / dist[0]);
		p.y += incr[0] * ((d.y - p.y) / dist[0]);
		dist[0] -= incr[0];
		dist[1] -= incr[1];
	}
	ft_printf("%i points plotted\n", ret);
}

 void	point_to_rombus(t_point p, int value, t_mlx *mlx)
{
	int				i;
	t_point 		vertex[6];

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
	fill_area(vertex[0], vertex[2], vertex[5], mlx);
	fill_area(vertex[0], vertex[2], vertex[4], mlx);
	fill_area(vertex[0], vertex[3], vertex[5], mlx);
	fill_area(vertex[0], vertex[3], vertex[5], mlx);
	fill_area(vertex[1], vertex[2], vertex[4], mlx);
	fill_area(vertex[1], vertex[2], vertex[5], mlx);
	fill_area(vertex[1], vertex[3], vertex[4], mlx);
	fill_area(vertex[1], vertex[3], vertex[5], mlx);
	/* fill_area(vertex[0], vertex[2], vertex[5], 0xFF0000, mlx);
	fill_area(vertex[0], vertex[2], vertex[4], 0x2FFFA2, mlx);
	fill_area(vertex[0], vertex[3], vertex[5], 0x0000FF, mlx);
	fill_area(vertex[0], vertex[3], vertex[5], 0x00FFFF, mlx);
	fill_area(vertex[1], vertex[2], vertex[4], 0xFF0000, mlx);
	fill_area(vertex[1], vertex[2], vertex[5], 0xFFFF00, mlx);
	fill_area(vertex[1], vertex[3], vertex[4], 0x0000FF, mlx);
	fill_area(vertex[1], vertex[3], vertex[5], 0xD6108F, mlx); */
	//put_data(live_points, 0xD6108F, mlx);
}

t_point	rotate_point(t_point p, t_mlx *mlx)
{
	float	temp_x;
	float	temp_y;
	t_point	new_point;

	//JUST FOR TESTING
	to_zero(&mlx->data[0]);

	new_point = p;
	new_point.z -= mlx->data[0].z;
	new_point.x -= mlx->data[0].x;
	new_point.y -= mlx->data[0].y;
	
	// Apply rotation around the X-axis
	temp_y = new_point.y;
	new_point.y = new_point.y * cos(mlx->plane.r_x) - new_point.z * sin(mlx->plane.r_x);
	new_point.z = temp_y * sin(mlx->plane.r_x) + new_point.z * cos(mlx->plane.r_x);

	// Apply rotation around the Y-axis
	temp_x = new_point.x;
	new_point.x = new_point.x * cos(mlx->plane.r_y) + new_point.z * sin(mlx->plane.r_y);
	new_point.z = -temp_x * sin(mlx->plane.r_y) + new_point.z * cos(mlx->plane.r_y);

	// Translate the object so that its center is at the origin
	new_point.z += mlx->data[0].z;
	new_point.x += mlx->data[0].x;
	new_point.y += mlx->data[0].y;
	return (new_point);
}

/* Takes a t_point as a parameter and plots it to the image */
void	put_point(t_point p, int color, t_mlx *mlx)
{
	int		x;
	int		y;
	t_point	plot;
	
//	plot = rotate_point(p, mlx);
	plot = p;
	
	// Apply the projection and translation to screen coordinates
	x = mlx->plane.origin.x + plot.x;
	y = mlx->plane.origin.y + plot.y + mlx->plane.r_z;
	
	// If the point is off-screen, do not draw it
	if (x < 0 || y < 0 || x >= mlx->win_x || y >= mlx->win_y)
		return ;
//	printf("putting (%f, %f, %f) = [%i, %i]\n", p.z, p.x, p.y, x, y);
	my_pixel_put(mlx, x, y, p.z, color);
}

void	put_data(int color, t_mlx *mlx)
{
	int				i;
	t_point_list	*list;

	i = 0;
	list = mlx->live_points;
	while (list != NULL)
	{
		if (i % (9840 / 1) == 0)
			color += 10000;
		list->point = rotate_point(list->point, mlx);
		//printf("putting: (%f, %f, %f)\n", list->point.x, list->point.y, list->point.z);
		put_point(list->point, color, mlx);
		list = list->next;
		i++;
	}
}

void	plot_data(t_mlx *mlx)
{
	(*mlx).img->img = mlx_new_image((*mlx).mlx, (*mlx).win_x, (*mlx).win_y);
	(*mlx).img->addr = mlx_get_data_addr((*mlx).img->img, &(*mlx).img
			->bits_per_pixel, &(*mlx).img->line_length, &(*mlx).img->endian);
	mlx->z_img = (float *)malloc(mlx->win_y * mlx->img->line_length * mlx->img->bits_per_pixel * sizeof(float));
	if (!mlx->img->img || !mlx->img->addr || !mlx->z_img)
		return ;

	//point_to_rombus(a, 356, mlx);
	put_data(0xD6108F, mlx);

	//printf("ORIGIN: (%f, %f, %f)\n", mlx->plane.origin.x, mlx->plane.origin.y, mlx->plane.origin.z);
	my_pixel_put(mlx, mlx->plane.origin.x, mlx->plane.origin.y, mlx->plane.origin.z, 0xFF0000); //RED
//	put_point(a, 0x00FFFF, mlx); //YELLOW?
//	put_point(b, 0x00FFFF, mlx); //YELLOW?
//	put_point(c, 0x00FFFF, mlx); //YELLOW?
	mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img->img, 0, 0);
	free(mlx->z_img);
	mlx_destroy_image((*mlx).mlx, (*mlx).img->img);
}

int	get_data(t_mlx *mlx)
{
	
	t_point	a;
	t_point	b;
	t_point	c;

	a.x = 0;
	a.y = 0;
	a.z = 0;
	b.x = 100;
	b.y = 0;
	b.z = 0;
	c.x = 0;
	c.y = -100;
	c.z = 0;

	//fill_area(a, b, c, mlx);

	point_to_rombus(a, 365, mlx);

	mlx->data = (t_point *)malloc(1 * sizeof(t_point));
	ft_printf("centre=(%i, %i, %i)\n", mlx->data[0].z, mlx->data[0].x, mlx->data[0].y);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_mlx	*mlx;
	
	(void)argc; (void)argv;
	mlx = (t_mlx *)malloc(1 * sizeof(t_mlx));
	if (juice_the_pc(mlx))
	{
		free(mlx);
		return (1);
	}
	if (!get_data(mlx))
		return (1);
	plot_data(mlx);
//	ft_printf("%s\n", argv[1]);
	/* if (!data_parser(argv[1]))
	{
		clean_exit(mlx);
		return (1);
	}
	else
		ft_printf("ALL GOOD\n"); */
	mlx_mouse_hook(mlx->win, &handle_mouse, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, &clean_exit, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, &clean_exit, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
