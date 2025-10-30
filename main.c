/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:54:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/18 03:22:16 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	plot_data(t_mlx *mlx);

/* we should be taking into accounnt the depth of the point,
but we're not handling black points priority. */
void	my_pixel_put(void *my_struct, int x, int y, float z, unsigned int color)
{
	t_mlx	*mlx;
	char	*dst;
	float	*z_dest;
	
	if (!my_struct)
		return ;
	mlx = (t_mlx *)my_struct;

	//printf("putting (%i, %i, %f), with color %x\n", x, y, z, color);
	// If the point is off-screen, do not draw it
	if (x < 0 || y < 0 || /* z > 0 || */ x >= mlx->win_x || y >= mlx->win_y)
		return ;
	dst = mlx->img->addr + (y * mlx->img->line_length + x * (mlx->img->bits_per_pixel / sizeof(int *)));
	z_dest = mlx->z_img + (y * mlx->img->line_length + x * (mlx->img->bits_per_pixel / sizeof(float *)));
	if (*dst != 0x0 && *z_dest > z)
		return ;
	*(unsigned int *)dst = color;
	*(float *)z_dest = z;
}

int		exclude_ex(void *my_struct, t_obj_list *obj)
{
	t_values		*data;
	static int	i;
	t_mlx	*mlx;
	
	(void)my_struct; (void)obj; (void)data; (void)mlx; (void)i;
	if (!my_struct)
		return (1);
	mlx = (t_mlx *)my_struct;
	data = (t_values *)obj->data;
	/* if (i % 1000 == 0)
	 	printf("value=%f\n mana=%f\n", data->error, mlx->setty.mana);
	i++; */
	if ((obj->tag == DATA && ((mlx->setty.sel_y <= 0 && (obj->origin.y == mlx->setty.sel_y))
		|| (mlx->setty.sel_x > 0 && mlx->setty.sel_y > 0 && mlx->setty.sel_z > 0))
		&& (/* mlx->setty.mana <= 0 ||  */data->error < mlx->setty.mana))
		|| obj->tag != DATA)
		return (0);
	return (1);
}

int	release(int keysym, t_mlx *mlx)
{
	(void)mlx;
	if (keysym == 7 || keysym == 1)
	{
		mlx->setty.right_click = 0;
	}
	//ft_printf("released: %i\n", keysym);
	return (0);
}

int	mouse_drag(t_mlx *mlx)
{
	static unsigned int frame;
	int	x;
	int	y;

	if (mlx->setty.right_click != 0)
	{
		//ft_printf("pressed!!!\n");
		mlx_mouse_get_pos(mlx->win, &x, &y);
		mlx->duck.plane.xoffset += (x - mlx->xmouse_s) / mlx->duck.plane.scale;
		mlx->duck.plane.yoffset += (y - mlx->ymouse_s) / mlx->duck.plane.scale;

		mlx->xmouse_s = x;
		mlx->ymouse_s = y;
		if (frame % 100 == 0)
		{
			//printf("frame[%u]=(%f, %f)\n", frame, mlx->plane.origin.x, mlx->plane.origin.y);
			plot_data(mlx);
		}
		frame++;
	}
	return (0);
}

int	show_cool_data(t_mlx *mlx)
{
	char string[] = "BWAHAHA";
	
	mlx_string_put(mlx->mlx, mlx->win, 100, 100, 0xff00ff, string);
	my_pixel_put(mlx, 100, 100, 10000, 0xff00ff);
	return (0);
}

/* sets a point's cordinate to zero */
t_point	*to_zero(t_point *p)
{
	p->z = 0.0f;
	p->x = 0.0f;
	p->y = 0.0f;
	return (p);
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
	//put_data(mlx->duck, &exclude_ex, &my_pixel_put);
	put_data_thread(&mlx->duck, &exclude_ex, &my_pixel_put);
	my_pixel_put(mlx, 100, 100, 10000, 0xff00ff);
	//ft_printf("daata put!\n");
	//printf("ORIGIN: (%f, %f, %f)\n", mlx->plane.origin.x, mlx->plane.origin.y, mlx->plane.origin.z);
	to_zero(&a);
	put_point(a, 0x00FFFF, &my_pixel_put, &mlx->duck);
	//my_pixel_put(mlx, mlx->plane.origin.x, mlx->plane.origin.y, mlx->plane.origin.z, 0xFF0000); //RED
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

/* ZED Deafult main */
int	main(int argc, char *argv[])
{
	t_mlx	mlx;
	
	if (juice_the_pc(argv, &mlx))
		return (1);
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
	if (!get_zed_data(argv, 0, &mlx))
		return (1);
	clock_t t; 
	t = clock(); 
	plot_data(&mlx);
	t = clock() - t; 
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
	printf("PLOT_DATA took %f seconds to execute \n", time_taken); 
	mlx_mouse_hook(mlx.win, &handle_mouse, &mlx);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &handle_keypress, &mlx);
	mlx_hook(mlx.win, DestroyNotify, StructureNotifyMask, &clean_exit, &mlx);

	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, &release, &mlx);
	mlx_loop_hook(mlx.mlx, &mouse_drag, &mlx);
	
	mlx_loop(mlx.mlx);
	return (0);
}

