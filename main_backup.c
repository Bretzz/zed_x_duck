/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:54:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/26 23:29:15 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	my_pixel_put(t_img *data, int x, int y, int color);
void	put_point(t_point p, int color, t_mlx *mlx);
void	plot_data(t_mlx *mlx);

void	my_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

/* takes 2 3D points as parameters.
returns the distance (float) between them. */
float	ft_distf(t_point a, t_point b)
{
	return (sqrtf(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)) + ((a.z - b.z) * (a.z - b.z))));
}

float	ft_absf(float f)
{
	if (f < 0)
		return (f * -1.0f);
	return (f);
}

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

int	point_equal(t_point a, t_point b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (1);
	return (0);
}

t_point	any_not_obtuse(t_point a, t_point b, t_point c)
{
	if (ft_anglef(b, a, c) < MY_PI / 2)
		return (a);
	if (ft_anglef(a, b, c) < MY_PI / 2)
		return (b);
	else
		return (c);
}

/* takes 3 2D points as parameters and fill the area inbetween them */
void	fill_area(t_point a, t_point b, t_point c, int color, t_mlx *mlx)
{
	int		ret;
	float	incr[3];
	float	dist[3];
	t_point	p;
	t_point	d;
	t_point	t;
	t_point	temp_p;
	t_point	temp_t;
	
	p = any_not_obtuse(a, b, c); //point that moves along a side
	d = any_not_obtuse(c, b, a); //point to move towards
	t = a; //point that is neither p nor d
	if (point_equal(t, p) || point_equal(t, d))
		t = b;
	if (point_equal(t, p) || point_equal(t, d))
		t = c;
	dist[0] = ft_distf(p, d);
	incr[0] = dist[0] / 1000;
	dist[1] = ft_distf(p, t);
	incr[1] = dist[1] / 1000;
	incr[2] = 1.0f;
	temp_t = p;
	ret = 0;
	while (dist[1] > 1.0f)
	{
		temp_p = p;
		dist[2] = ft_distf(temp_p, temp_t);
		while (dist[2] > 1.0f)
		{
//			ft_printf("gatto????\n");
//			printf("dist3=%f\n", dist3);
//			printf("temp_p = (%f, %f, %f)\n", temp_p.x, temp_p.y, temp_p.z);
			put_point(temp_p, color, mlx);
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
	int		i;
	t_point vertex[6];

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
	fill_area(vertex[0], vertex[2], vertex[5], 0xFF0000, mlx);
	fill_area(vertex[0], vertex[2], vertex[4], 0x2FFFA2, mlx);
	fill_area(vertex[0], vertex[3], vertex[5], 0x0000FF, mlx);
	fill_area(vertex[0], vertex[3], vertex[5], 0x00FFFF, mlx);
	fill_area(vertex[1], vertex[2], vertex[4], 0xFF0000, mlx);
	fill_area(vertex[1], vertex[2], vertex[5], 0xFFFF00, mlx);
	fill_area(vertex[1], vertex[3], vertex[4], 0x0000FF, mlx);
	fill_area(vertex[1], vertex[3], vertex[5], 0xD6108F, mlx);

}

/* Takes a t_point as a parameter and plots it to the image */
void	put_point(t_point p, int color, t_mlx *mlx)
{
	int		x;
	int		y;
	t_point	plot;
	float	temp_x;
	float	temp_y;

	mlx->data[0].z = 0;
	mlx->data[0].x = 0;
	mlx->data[0].y = 0;

	plot = p;
	// Translate the object so that its center is at the origin
	plot.z -= mlx->data[0].z;
	plot.x -= mlx->data[0].x;
	plot.y -= mlx->data[0].y;
	
	// Apply rotation around the X-axis
	temp_y = plot.y;
	plot.y = plot.y * cos(mlx->plane.r_x) - plot.z * sin(mlx->plane.r_x);
	plot.z = temp_y * sin(mlx->plane.r_x) + plot.z * cos(mlx->plane.r_x);

	// Apply rotation around the Y-axis
	temp_x = plot.x;
	plot.x = plot.x * cos(mlx->plane.r_y) + plot.z * sin(mlx->plane.r_y);
	plot.z = -temp_x * sin(mlx->plane.r_y) + plot.z * cos(mlx->plane.r_y);

	// Translate the object so that its center is at the origin
	plot.z += mlx->data[0].z;
	plot.x += mlx->data[0].x;
	plot.y += mlx->data[0].y;
	
//	ft_printf("micio sus????\n");
	
	// Apply the projection and translation to screen coordinates
	x = mlx->plane.origin.x + plot.x;
	y = mlx->plane.origin.y + plot.y + mlx->plane.r_z;
	
	// If the point is off-screen, do not draw it
	if (x < 0 || y < 0 || x >= mlx->win_x || y >= mlx->win_y)
		return ;
//	printf("putting (%f, %f, %f) = [%i, %i]\n", p.z, p.x, p.y, x, y);
	my_pixel_put((*mlx).img, x, y, color);
}

t_point	*to_zero(t_point *p)
{
	p->z = 0;
	p->x = 0;
	p->y = 0;
	return (p);
}

void	plot_data(t_mlx *mlx)
{
	//int		i;
	t_point	a;
	t_point	b;
	t_point	c;

	(*mlx).img->img = mlx_new_image((*mlx).mlx, (*mlx).win_x, (*mlx).win_y);
	(*mlx).img->addr = mlx_get_data_addr((*mlx).img->img, &(*mlx).img
			->bits_per_pixel, &(*mlx).img->line_length, &(*mlx).img->endian);

	a.x = 0;
	a.y = 0;
	a.z = 0;
	b.x = 200;
	b.y = -79;
	b.z = 0;
	c.x = -100;
	c.y = -300;
	c.z = -123;

	//i = 1;
	/* printf("mod=%f\n", ft_distf(a, b));
	printf("areaABC=%f\n", ft_areaf(a, b, c)); */
/* 	printf("bac=%f\n", ft_anglef(a, b, c));
	printf("cab=%f\n", ft_anglef(a, c, b));
	printf("90=%f\n", MY_PI / 2); */

	point_to_rombus(a, 356, mlx);
	//fill_area(a, b, c, mlx);

//	point_to_sphere(mlx->data[i], 10, mlx);
	/* put_point(a, 0x0000FF00, mlx); //GREEN
	put_point(b, 0x0000FF00, mlx); //GREEN */
//	point_to_sphere(a, 10, mlx); //GREEN
//	point_to_sphere(b, 10, mlx); //GREEN
	/* while (i < 801)
	{
		if (i % 100 == 0 && !a.z && !a.x && !a.y)
			a = mlx->data[i];
		else if (i % 100 == 0 && !b.z && !b.x && !b.y)
			b = mlx->data[i];
		else if (i % 100 == 0 && !c.z && !c.x && !c.y)
			c = mlx->data[i];
		if (a.z && b.x && c.y)
		{
//			ft_printf("plotting (%i, %i, %i)\n", mlx->data[i].z, mlx->data[i].x, mlx->data[i].y);
			fill_area(a, b, c, mlx);
			to_zero(&a);
			to_zero(&b);
			to_zero(&c);
		}
		//point_to_sphere(mlx->data[i], 3, mlx);
		//put_point(mlx->data[i], 0x0000FF00, mlx); //GREEN
		i++;
	} */
	my_pixel_put((*mlx).img, mlx->plane.origin.x, mlx->plane.origin.y, 0xFF0000); //RED
//	put_point(a, 0x00FFFF, mlx); //YELLOW?
//	put_point(b, 0x00FFFF, mlx); //YELLOW?
//	put_point(c, 0x00FFFF, mlx); //YELLOW?
	mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img->img, 0, 0);
	mlx_destroy_image((*mlx).mlx, (*mlx).img->img);
}

int	get_data(t_mlx *mlx)
{
	int	i;
	int	j;
	int	side_len;
	
	side_len = 100;
	mlx->data = (t_point *)malloc((side_len * 8  + 1) * sizeof(t_point));
	if (!mlx->data)
		return (0);
//	data[100] = (t_point)0;
	i = 1;
	j = 0;
	while (i < side_len) //asse X
	{
		mlx->data[i].z = 0;
		mlx->data[i].x = j;
		mlx->data[i].y = 0;
		i++;
		j++;
	}
	j = 0;
	while (i < side_len * 2) //asse Y
	{
		mlx->data[i].z = 0;
		mlx->data[i].x = side_len - 1;
		mlx->data[i].y = j;
		i++;
		j++;
	}
	j = 0;
	while (i < side_len * 3) //asse Z
	{
		mlx->data[i].z = 0;
		mlx->data[i].x = side_len - 1 - j;
		mlx->data[i].y = side_len - 1;
		i++;
		j++;
	}
	j = 0;
	while (i < side_len * 4) //asse Z
	{
		mlx->data[i].z = 0;
		mlx->data[i].x = 0;
		mlx->data[i].y = side_len - 1 - j;
		i++;
		j++;
	}
	j = 0;
	while (i < side_len * 5) //asse X
	{
		mlx->data[i].z = side_len - 1;
		mlx->data[i].x = j;
		mlx->data[i].y = 0;
		i++;
		j++;
	}
	j = 0;
	while (i < side_len * 6) //asse Y
	{
		mlx->data[i].z = side_len - 1;
		mlx->data[i].x = side_len - 1;
		mlx->data[i].y = j;
		i++;
		j++;
	}
	j = 0;
	while (i < side_len * 7) //asse Z
	{
		mlx->data[i].z = side_len - 1;
		mlx->data[i].x = side_len - 1 - j;
		mlx->data[i].y = side_len - 1;
		i++;
		j++;
	}
	j = 0;
	while (i < side_len * 8) //asse Z
	{
		mlx->data[i].z = side_len - 1;
		mlx->data[i].x = 0;
		mlx->data[i].y = side_len - 1 - j;
		i++;
		j++;
	}
	mlx->data[0] = get_centre(&mlx->data[1], side_len * 8);
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
