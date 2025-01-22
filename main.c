/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:54:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/22 15:39:57 by totommi          ###   ########.fr       */
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

/* Takes a t_point as a parameter and plots it to the image */
void	put_point(t_point p, int color, t_mlx *mlx)
{
	int	x;
	int	y;
	
	if (p.z == 0)
		p.z = 1;
	x = mlx->plane.origin.x + (p.x * cos(mlx->plane.r_x)) + (sin(mlx->plane.r_x) * p.z);
	y = mlx->plane.origin.y + (p.y * cos(mlx->plane.r_y)) + (sin(mlx->plane.r_y) * p.z);
//	ft_printf("putting (%i, %i, %i) = [%i, %i]\n", p.z, p.x, p.y, x, y);
	my_pixel_put((*mlx).img, x, y, color);
}

void	plot_data(t_mlx *mlx)
{
	int		i;

	ft_printf("%i\n", mlx->data[1].z);
	ft_printf("%i\n", mlx->data[1].x);
	ft_printf("%i\n", mlx->data[1].y);

	(*mlx).img->img = mlx_new_image((*mlx).mlx, (*mlx).win_x, (*mlx).win_y);
	ft_printf("huh?????????\n");
	(*mlx).img->addr = mlx_get_data_addr((*mlx).img->img, &(*mlx).img
			->bits_per_pixel, &(*mlx).img->line_length, &(*mlx).img->endian);
	ft_printf("huh?\n");
	i = 0;
	while (i < 100)
	{
	//	ft_printf("plotting (%i, %i, %i)\n", mlx->data[i].x, mlx->data[i].y, mlx->data[i].z);
		put_point(mlx->data[i], 0x0000FF00, mlx); //GREEN
		i++;
	}
	//put_point(mlx->plane.origin, 0x00FF0000, mlx);
	my_pixel_put((*mlx).img, mlx->plane.origin.x, mlx->plane.origin.y, 0xFF0000); //RED

	mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img->img, 0, 0);
	mlx_destroy_image((*mlx).mlx, (*mlx).img->img);
}

int	main(int argc, char *argv[])
{
	int		i;
	t_mlx	*mlx;
	
	(void)argc; /* (void)argv; */
	mlx = (t_mlx *)malloc(1 * sizeof(t_mlx));
	if (juice_the_pc(mlx))
	{
		free(mlx);
		return (1);
	}

	mlx->data = (t_point *)malloc(100 * sizeof(t_point));
	if (!mlx->data)
		return (1);
//	data[100] = (t_point)0;
	i = 0;
	while (i < 33) //asse X
	{
//		mlx->data[i] = (t_point *)malloc(1 * sizeof(t_point));
		mlx->data[i].z = 0;
		mlx->data[i].x = i;
		mlx->data[i].y = 0;
		i++;
	}
	while (i < 66) //asse Y
	{
//		mlx->data[i] = (t_point *)malloc(1 * sizeof(t_point));
		mlx->data[i].z = 0;
		mlx->data[i].x = 0;
		mlx->data[i].y = i - 33;
		i++;
	}
	while (i < 99) //asse Z
	{
//		mlx->data[i] = (t_point *)malloc(1 * sizeof(t_point));
		mlx->data[i].z = i - 66;
		mlx->data[i].x = 0;
		mlx->data[i].y = 0;
		i++;
	}
//	plot_data(mlx);
//	ft_printf("%s\n", argv[1]);
	if (!data_parser(argv[1]))
	{
		clean_exit(mlx);
		return (1);
	}
	else
		ft_printf("ALL GOOD\n");
/*	mlx_mouse_hook(mlx->win, &handle_mouse, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, &clean_exit, mlx);
	mlx_loop(mlx->mlx); */
	return (0);
}
