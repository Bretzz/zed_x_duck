/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:47:59 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/12 15:40:50 by totommi          ###   ########.fr       */
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
	ft_free_point_list(mlx->data.list);
	ft_free_obj_list(mlx->live_objs);
	free(mlx->mlx);
	free(mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

/* XK_Up XK_Right XK_Down, XK_Left */
int	handle_mouse(int keysym, int x, int y, t_mlx *mlx)
{
	UNUSED(x);
	UNUSED(y);
	UNUSED(mlx);
	ft_printf("Mousething N.%d\n", keysym);
	return (0);
}

int	handle_keypress(int keysym, t_mlx *mlx)
{
	float			angle;
	static int		file;

	angle = 1.6 * MY_PI / 180;
	if (keysym == XK_Up || keysym == 126)
		mlx->plane.r_x += -angle;
	else if (keysym == XK_Down || keysym == 125)
		mlx->plane.r_x += angle;
	else if (keysym == XK_Right || keysym == 124)
		mlx->plane.r_y += -angle;
	else if (keysym == XK_Left || keysym == 123)
		mlx->plane.r_y += angle;
	else if (keysym == XK_a || keysym == 0)
		mlx->plane.x_shift -= 10;
	else if (keysym == XK_d || keysym == 2)
		mlx->plane.x_shift += 10;
	else if (keysym == XK_w || keysym == 13)
		mlx->plane.y_shift -= 10;
	else if (keysym == XK_s || keysym == 1)
		mlx->plane.y_shift += 10;
	else if (keysym == XK_equal || keysym == 24)
		mlx->setty.mana += 0.1f;
	else if (keysym == XK_minus || keysym == 27)
		mlx->setty.mana -= 0.1f;
	else if (keysym == XK_i || keysym == 34)
	{
		if (mlx->setty.sel_y > 0 || mlx->setty.sel_y <= -600)
			mlx->setty.sel_y = 0;
		else
			mlx->setty.sel_y -= 40;
		mlx->setty.sel_x = 0;
		mlx->setty.sel_z = 0;
	}
	else if (keysym == XK_k || keysym == 40)
	{
		if (mlx->setty.sel_y > 0 || mlx->setty.sel_y == 0)
			mlx->setty.sel_y = -600;
		else
			mlx->setty.sel_y += 40;
		mlx->setty.sel_x = 0;
		mlx->setty.sel_z = 0;
	}
	else if (keysym == XK_r || keysym == 15)
	{
		mlx->plane.r_y = (float)0;
		mlx->plane.r_x = (float)0;
		mlx->plane.r_z = (float)0;
		mlx->setty.sel_x = 1;
		mlx->setty.sel_y = 1;
		mlx->setty.sel_z = 1;
	}
	else if (keysym == XK_p || keysym == 35)
	{
		ft_free_obj_list(mlx->live_objs);
		ft_free_point_list(mlx->data.list);
		mlx->live_objs = NULL;
		mlx->data.list = NULL;
		file += 1;
		get_zed_data(mlx->argv, file, mlx);
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
