/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:54:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/31 19:33:41 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	my_pixel_put(t_mlx *mlx, int x, int y, float z, int color);
void	put_point(t_point p, int color, t_mlx *mlx);
void	plot_data(t_mlx *mlx);

/* we should be taking into accounnt the depth of the point,
but we're not handling black points priority. */
void	my_pixel_put(t_mlx *mlx, int x, int y, float z, int color)
{
	char	*dst;
	float	*z_dest;
	
//	printf("putting2: [%i, %i]:%f\n", x, y, z);
	dst = mlx->img->addr + (y * mlx->img->line_length + x * (mlx->img->bits_per_pixel / sizeof(int *)));
	z_dest = mlx->z_img + (y * mlx->img->line_length + x * (mlx->img->bits_per_pixel / sizeof(float *)));
	if (*dst != 0x0 && *z_dest > z)
		return ;
	*(unsigned int *)dst = color;
	*(float *)z_dest = z;
}

void	rotate_list(t_point_list *list, t_mlx *mlx)
{
	while (list != NULL)
	{
		//printf("rotating (%f, %f, %f)\n", list->point.x, list->point.y, list->point.z);
		list->point = rotate_point(list->point, mlx);
		list = list->next;
	}
}

void	put_data(t_mlx *mlx)
{
	int				color = 0x0Fa23F;
	int				i;
	t_point_list	*list;

	i = 0;
	list = mlx->live_points;
	while (list != NULL)
	{
		if (i % (16649 / 1) == 0) //128=16649 //365=133757
			color += 10000;
//		list->color = color;
		list->point = rotate_point(list->point, mlx);
		//printf("putting: (%f, %f, %f)\n", list->point.x, list->point.y, list->point.z);
		put_point(list->point, list->color, mlx);
		list = list->next;
		i++;
	}
}

void	plot_data(t_mlx *mlx)
{
	t_point a;

	(*mlx).img->img = mlx_new_image((*mlx).mlx, (*mlx).win_x, (*mlx).win_y);
	(*mlx).img->addr = mlx_get_data_addr((*mlx).img->img, &(*mlx).img
			->bits_per_pixel, &(*mlx).img->line_length, &(*mlx).img->endian);
	mlx->z_img = (float *)malloc(mlx->win_y * mlx->img->line_length * mlx->img->bits_per_pixel * sizeof(float));
	if (!mlx->img->img || !mlx->img->addr || !mlx->z_img)
		return ;

	//point_to_rombus(a, 356, mlx);
	put_data(mlx);

	//printf("ORIGIN: (%f, %f, %f)\n", mlx->plane.origin.x, mlx->plane.origin.y, mlx->plane.origin.z);
	to_zero(&a);
	put_point(a, 0x00FFFF, mlx);
	my_pixel_put(mlx, mlx->plane.origin.x, mlx->plane.origin.y, mlx->plane.origin.z, 0xFF0000); //RED
//	put_point(a, 0x00FFFF, mlx); //YELLOW?
//	put_point(b, 0x00FFFF, mlx); //YELLOW?
//	put_point(c, 0x00FFFF, mlx); //YELLOW?
	mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img->img, 0, 0);
	free(mlx->z_img);
	mlx->z_img = NULL;
	mlx_destroy_image((*mlx).mlx, (*mlx).img->img);
}

/* this function does the magic.
if you pass a (1, 1, 1), it returns the equivalent in the axis we just plot
(actually just swaps the y coordinate :D) */
t_point	norm(t_point p)
{
	t_point	norm_p;

	norm_p = p;
	norm_p.y *= -1;
	return (norm_p);
}

/* takes an array of points as parameter.
fills the mlx->live points list with the shape you want to make from the point
RETURNS: the number of points added, -1 on error*/
int	data_birth(t_point *data, t_mlx *mlx)
{
	int	i;
	int	points;

	points = 0;
	i = 0;
	while (i < 1000)
	{
		points += point_to_rombus(data[i], 2, mlx);
		i++;
	}
	points += place_axis(555.0f, 555.0f, -500.0f, mlx);
	return (points);
}

int	get_data(t_mlx *mlx)
{
	int	i;
	int	points;
	int	axis_pts;
	t_point	a;
	t_point	b;
	t_point	c;
	t_point p;

	mlx->data = (t_point *)malloc(1001 * sizeof(t_point));
	if (!mlx->data)
		return (0);
	to_zero(&p);
	i = 1;
	while (i < 1001)
	{
		p.z = (float)rand()/(float)(RAND_MAX/1000.0f);
		p.x = (float)rand()/(float)(RAND_MAX/1000.0f);
		p.y = (float)rand()/(float)(RAND_MAX/500.0f);
		mlx->data[i] = norm(p);
		i++;
	}
	
	a.x = 0;
	a.y = 0;
	a.z = 0;
	b.x = 23;
	b.y = 157;
	b.z = -10;
	c.x = 50;
	c.y = 50;
	c.z = 50;

	a = norm(a); b = norm(b); c = norm(c);

	points = 0;
	//triangle
	//points += fill_area(a, b, c, 0xf77f01, mlx);

	(void)b; (void)c; (void)points; (void)axis_pts;
	//points += point_to_rombus(a, 12, mlx);
	//points += point_to_rombus(c, 5, mlx);
	
	//must do
	//axis_pts = place_axis(555.0f, 333.0f, -333.0f, mlx);
	//ft_printf("%i total points added\n", axis_pts + points);
	
	/* to_zero(&mlx->data[0]);
	rotate_list(mlx->live_points, mlx); */
	//mlx->data[0] = get_list_centre(mlx->live_points, axis_pts, points);
	mlx->data[0] = get_centre(&mlx->data[1], 100);

	printf("centre=(%f, %f, %f)\n", mlx->data[0].x, mlx->data[0].y, mlx->data[0].z);
	ft_printf("data generation complete\n");
	ft_printf("%i points added\n", data_birth(&mlx->data[1], mlx));
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

