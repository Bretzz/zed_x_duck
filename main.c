/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:54:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/23 15:16:08 by topiana-         ###   ########.fr       */
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
	t_point	centre;
	int	i;

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

void	point_to_sphere(t_point p, int value, t_mlx *mlx)
{
	int		j;
	float	i;
	t_point	runner;

	runner = p;

	j = 0;
	while (j < 2 * value)
	{
		i = 0.0f;
		while (i < (2 * 3.1415f))
		{
			runner.z = value - j;
			runner.x = p.x + j * cos(i);
			runner.y = p.y + j * sin(i);
			put_point(runner, 0x0000FF00, mlx);
			i += 0.01f;
		}
		j++;
	}


	/* j = 0;
	while (j < 10)
	{
		i = 0.0f;
		while (i < (2 * 3.1415f))
		{
//			runner.z = p.z * j + value * cos(i);
			runner.x = p.x + value * cos(i);
			runner.y = p.y + value * sin(i);
			put_point(runner, 0x0000FF00, mlx);
			i += 0.01f;
		}
		j++;
	} */
	/* i = 0.0f;
	while (i < (2 * 3.1415f))
	{
		runner.x = p.x;
		runner.y = p.y + value * sin(i);
		put_point(runner, 0x0000FF00, mlx);
		i += 0.1f;
	} */
}

/* Takes a t_point as a parameter and plots it to the image */
void	put_point(t_point p, int color, t_mlx *mlx)
{
	int	x;
	int	y;
	t_point	plot;
	int temp_x;
	int	temp_y;

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
	
	// Apply the projection and translation to screen coordinates
	x = mlx->plane.origin.x + plot.x;
	y = mlx->plane.origin.y + plot.y + mlx->plane.r_z;
	
	// If the point is off-screen, do not draw it
	if (x < 0 || y < 0 || x > mlx->win_x || y > mlx->win_y)
		return ;
//	ft_printf("putting (%i, %i, %i) = [%i, %i]\n", p.z, p.x, p.y, x, y);
	my_pixel_put((*mlx).img, x, y, color);
}

void	plot_data(t_mlx *mlx)
{
	int		i;
	t_point	a;
	t_point	b;

	(*mlx).img->img = mlx_new_image((*mlx).mlx, (*mlx).win_x, (*mlx).win_y);
	(*mlx).img->addr = mlx_get_data_addr((*mlx).img->img, &(*mlx).img
			->bits_per_pixel, &(*mlx).img->line_length, &(*mlx).img->endian);

	a.x = 10;
	a.y = 10;
	a.z = 100;
	b.x = -10;
	b.y = -10;
	b.z = -100;

	i = 1;
	point_to_sphere(mlx->data[i], 10, mlx);
	/* put_point(a, 0x0000FF00, mlx); //GREEN
	put_point(b, 0x0000FF00, mlx); //GREEN */
//	point_to_sphere(a, 10, mlx); //GREEN
//	point_to_sphere(b, 10, mlx); //GREEN
	/* while (i < 801)
	{
//		ft_printf("plotting (%i, %i, %i)\n", mlx->data[i].z, mlx->data[i].x, mlx->data[i].y);
		point_to_sphere(mlx->data[i], 3, mlx);
		//put_point(mlx->data[i], 0x0000FF00, mlx); //GREEN
		i++;
	} */
	my_pixel_put((*mlx).img, mlx->plane.origin.x, mlx->plane.origin.y, 0xFF0000); //RED

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
	mlx_loop(mlx->mlx);
	return (0);
}
