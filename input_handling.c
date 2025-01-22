/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:47:59 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/22 14:16:41 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	plot_data(t_mlx *mlx);

/*mlx and mlx->img are manually mallocated so we must manually free them
mlx->win and mlx->mlx are cleaned with built-in functions
(somehow mlx->mlx also needs to be freed manually)*/
int	clean_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
//	mlx_destroy_display(mlx->mlx);
	if (mlx->img)
		free(mlx->img);
	free(mlx->mlx);
	free(mlx->data);
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
//	ft_printf("XK_Up=%i\n", XK_Up);
	if (keysym == XK_Up)
	{
		ft_printf("going up! %i\n", keysym);
		mlx->plane.r_y -= (float)0.1;
	}
	if (keysym == XK_Down)
	{
		ft_printf("going down! %i\n", keysym);
		mlx->plane.r_y += (float)0.1;
	}
	if (keysym == XK_Right)
	{
		ft_printf("going right! %i\n", keysym);
		mlx->plane.r_x -= (float)0.1;
	}
	if (keysym == XK_Left)
	{
		ft_printf("going left! %i\n", keysym);
		mlx->plane.r_x += (float)0.1;
	}
	if (keysym == XK_w)
	{
		ft_printf("going up(?) %i\n", keysym);
		mlx->plane.r_z += (float)0.1;
	}
	if (keysym == XK_s)
	{
		ft_printf("going down(?) %i\n", keysym);
		mlx->plane.r_z -= (float)0.1;
	}
	if (keysym == XK_a)
	{
		ft_printf("going up(?) %i\n", keysym);
		mlx->plane.fov += (float)1;
	}
	if (keysym == XK_d)
	{
		ft_printf("going down(?) %i\n", keysym);
		mlx->plane.fov -= (float)1;
	}
	if (keysym == ESC_KEY)
	{
		clean_exit(mlx);
		return (0);
	}
	ft_printf("Keypress: %d\n", keysym);
	plot_data(mlx);
	return (0);
}
