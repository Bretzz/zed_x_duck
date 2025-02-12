/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:54:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/12 23:51:36 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	my_pixel_put(t_mlx *mlx, int x, int y, float z, int color);
void	plot_data(t_mlx *mlx);

int	show_cool_data(t_mlx *mlx)
{
	char string[] = "BWAHAHA";
	
	mlx_string_put(mlx->mlx, mlx->win, 100, 100, 0xff00ff, string);
	my_pixel_put(mlx, 100, 100, 10000, 0xff00ff);
	return (0);
}

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

void	plot_data(t_mlx *mlx)
{
	t_point a;

	mlx->img->img = mlx_new_image(mlx->mlx, mlx->win_x, mlx->win_y);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img
			->bits_per_pixel, &mlx->img->line_length, &mlx->img->endian);
	mlx->z_img = (float *)malloc(mlx->win_y * mlx->img->line_length * mlx->img->bits_per_pixel * sizeof(float));
	if (!mlx->img->img || !mlx->img->addr || !mlx->z_img)
		return ;

	//point_to_rombus(a, 356, mlx);
	//put_data(mlx);
	put_data_thread(mlx);
	my_pixel_put(mlx, 100, 100, 10000, 0xff00ff);
	
	//printf("ORIGIN: (%f, %f, %f)\n", mlx->plane.origin.x, mlx->plane.origin.y, mlx->plane.origin.z);
	to_zero(&a);
	put_point(a, 0x00FFFF, mlx);
	my_pixel_put(mlx, mlx->plane.origin.x, mlx->plane.origin.y, mlx->plane.origin.z, 0xFF0000); //RED
	//	put_point(a, 0x00FFFF, mlx); //YELLOW?
	//	put_point(b, 0x00FFFF, mlx); //YELLOW?
	//	put_point(c, 0x00FFFF, mlx); //YELLOW?
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	//ft_printf("ccc\n");
	show_cool_data(mlx);
	// ft_bzero(mlx->img->addr, mlx->win_y * mlx->win_x * 4/* 100 * sizeof(int *) *//* (mlx->win_y * mlx->img->line_length + mlx->win_x * (mlx->img->bits_per_pixel / sizeof(int *))) */);
	// ft_bzero(mlx->z_img, mlx->win_y * mlx->img->line_length * mlx->img->bits_per_pixel * sizeof(float));
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	//ft_printf("ddd\n");
	free(mlx->z_img);
	mlx->z_img = NULL;
}

int	fdf_main(int argc, char *argv[])
{
	t_mlx	*mlx;
	
	mlx = (t_mlx *)malloc(1 * sizeof(t_mlx));
	if (juice_the_pc(FDF, argv, mlx))
	{
		free(mlx);
		return (1);
	}
	ft_printf("PC JUICED!\n");
	ft_printf("argc=%i, argv[0]=%s\n", argc, argv[0]);
	if (!get_fdf_data(argv, mlx))
		return (1);
	plot_data(mlx);
	// if (!get_zed_data(argv, 0, mlx))
	// 	return (1);
	// clock_t t; 
	// t = clock(); 
	// plot_data(mlx);
	// t = clock() - t; 
	// double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
	// printf("PLOT_DATA took %f seconds to execute \n", time_taken); 
	mlx_mouse_hook(mlx->win, &handle_mouse, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, &clean_exit, mlx);
	//mlx_loop_hook(mlx->win, &show_cool_data, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}

/* ZED Deafult main */
int	zed_main(int argc, char *argv[])
{
	t_mlx	*mlx;
	
	mlx = (t_mlx *)malloc(1 * sizeof(t_mlx));
	if (juice_the_pc(ZED, argv, mlx))
	{
		free(mlx);
		return (1);
	}
	ft_printf("PC JUICED!\n");
	ft_printf("argc=%i, argv[0]=%s\n", argc, argv[0]);
//	ft_printf("%s\n", argv[1]);
	/* if (!data_parser(argv[1]))
	{
		clean_exit(mlx);
		return (1);
	}
	else
		ft_printf("ALL GOOD\n"); */
	if (!get_zed_data(argv, 0, mlx))
		return (1);
	clock_t t; 
	t = clock(); 
	plot_data(mlx);
	t = clock() - t; 
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
	printf("PLOT_DATA took %f seconds to execute \n", time_taken); 
	mlx_mouse_hook(mlx->win, &handle_mouse, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, &clean_exit, mlx);
	//mlx_loop_hook(mlx->win, &show_cool_data, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);
	if (!ft_strncmp("zed", argv[1], 3))
		zed_main(argc - 1, &argv[1]);
	else if (!ft_strncmp("fdf", argv[1], 3))
		fdf_main(argc - 1, &argv[1]);
	else
		ft_printf("dunno man...\n");
	return (0);
}

