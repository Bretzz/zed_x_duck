/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:47:59 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/31 15:40:01 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	plot_data(t_mlx *mlx);
int		clean_exit(t_mlx *mlx);
int		handle_mouse(int keysym, int x, int y, t_mlx *mlx);
int		handle_keypress(int keysym, t_mlx *mlx);

/*mlx and mlx->img are manually mallocated so we must manually free them
mlx->win and mlx->mlx are cleaned with built-in functions
(somehow mlx->mlx also needs to be freed manually)*/
int	clean_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	//mlx_destroy_display(mlx->mlx);
	if (mlx->img)
		free(mlx->img);
	if (mlx->z_img)
		free(mlx->z_img);
//	free both live_points and data.list
	free(mlx->mlx);
	free(mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

/* XK_Up XK_Right XK_Down, XK_Left */
int	handle_mouse(int keysym, int x, int y, t_mlx *mlx)
{
	UNUSED(x); UNUSED(y); UNUSED(mlx);
	ft_printf("Mousething N.%d\n", keysym);
	return (0);
}

int	handle_keypress(int keysym, t_mlx *mlx)
{
	static float	r[3];
	float			one_deg;

	one_deg = 1 * MY_PI / 180;

	mlx->plane.r_x = (float)0;
	mlx->plane.r_y = (float)0;
//	ft_printf("XK_Up=%i\n", XK_Up);
	if (keysym == XK_Up || keysym == 126)
	{
//		ft_printf("going up! %i\n", keysym);
		mlx->plane.r_x = -one_deg;
		mlx->plane.r_y = (float)0;
		mlx->plane.r_z = (float)0;
		r[1] += one_deg;
	}
	else if (keysym == XK_Down || keysym == 125)
	{
//		ft_printf("going down! %i\n", keysym);
		mlx->plane.r_x = one_deg;
		mlx->plane.r_y = (float)0;
		mlx->plane.r_z = (float)0;
		r[1] -= one_deg;
	}
	else if (keysym == XK_Right || keysym == 124)
	{
//		ft_printf("going right! %i\n", keysym);
		mlx->plane.r_y = -one_deg;
		mlx->plane.r_x = (float)0;
		mlx->plane.r_z = (float)0;
		r[2] += one_deg;
	}
	else if (keysym == XK_Left || keysym == 123)
	{
//		ft_printf("going left! %i\n", keysym);
		mlx->plane.r_y = one_deg;
		mlx->plane.r_x = (float)0;
		mlx->plane.r_z = (float)0;
		r[2] -= one_deg;
	}
	else if (keysym == XK_a)
	{
//		ft_printf("going up(?) %i\n", keysym);
		mlx->plane.r_z = one_deg;
		mlx->plane.r_x = (float)0;
		mlx->plane.r_y = (float)0;
		r[0] -= one_deg;
	}
	else if (keysym == XK_d)
	{
//		ft_printf("going down(?) %i\n", keysym);
		mlx->plane.r_z = -one_deg;
		mlx->plane.r_y = (float)0;
		mlx->plane.r_x = (float)0;
		r[0] += one_deg;
	}
	else if (keysym == XK_w || keysym == 13)
	{
//		ft_printf("going up(?) %i\n", keysym);
		mlx->plane.y_shift -= (float)10;
	}
	else if (keysym == XK_s || keysym == 1)
	{
//		ft_printf("going down(?) %i\n", keysym);
		mlx->plane.y_shift += (float)10;
	}
	else if (keysym == XK_r || keysym == 15)
	{
//		ft_printf("RESET %i\n", keysym);
		mlx->plane.r_z = (float)r[0];
		mlx->plane.r_x = (float)r[1];
		mlx->plane.r_y = (float)r[2];
		printf("r[0]=%f, r[1]=%f, r[2]=%f\n", r[0], r[1], r[2]);
		r[0] = 0;
		r[1] = 0;
		r[2] = 0;
	}
	else if (keysym == ESC_KEY)
	{
		clean_exit(mlx);
		return (0);
	}
	else
		ft_printf("Keypress: %d\n", keysym);
	plot_data(mlx);
	return (0);
}
