/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:47:59 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/18 03:38:50 by totommi          ###   ########.fr       */
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
	ft_free_data_list(mlx->data.list, &free);
	duck_free_obj_list(mlx->duck.live_objs, &free);
	free(mlx->mlx);
	//free(mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

/* XK_Up XK_Right XK_Down, XK_Left */
int	handle_mouse(int keysym, int x, int y, t_mlx *mlx)
{
	if (keysym == 1) // keysym == 1
	{
		mlx->setty.right_click = 1;
		ft_printf("RIGHT CLICK!!!\n");
		mlx->xmouse_s = x/*  + mlx->duck.plane.xoffset */;
		mlx->ymouse_s = y/*  + mlx->duck.plane.yoffset */;
	}
	else if (keysym == 5) //zoom(in);
	{
		mlx->duck.plane.xmouse_w = (float)(x / mlx->duck.plane.scale) + mlx->duck.plane.xoffset;
		mlx->duck.plane.ymouse_w = (float)(y / mlx->duck.plane.scale) + mlx->duck.plane.yoffset;
		//mlx->duck.plane.fov_diff = 0.01f;
		mlx->duck.plane.scale *= 1.019f; //scalechange = curr_fov - old_fov
		//printf("new scale=%f\n", mlx->duck.plane.scale);
		//printf("x-shifting=%f\n", ((float)x / mlx->win_x) / 0.01f);
		mlx->duck.plane.xoffset -= mlx->duck.plane.xmouse_w - ((float)(x / mlx->duck.plane.scale) + mlx->duck.plane.xoffset);
		mlx->duck.plane.yoffset -= mlx->duck.plane.ymouse_w - ((float)(y / mlx->duck.plane.scale) + mlx->duck.plane.yoffset);
		//printf("new origin=(%f,%f)\n", mlx->duck.plane.xoffset, mlx->duck.plane.yoffset);
	}
	else if (keysym == 4) //zoom(out);
	{
		mlx->duck.plane.xmouse_w = (float)(x / mlx->duck.plane.scale) + mlx->duck.plane.xoffset;
		mlx->duck.plane.ymouse_w = (float)(y / mlx->duck.plane.scale) + mlx->duck.plane.yoffset;
		//mlx->duck.plane.fov_diff = 0.01f;
		mlx->duck.plane.scale *= 0.981f;
		//printf("x-shifting=%f\n", ((float)x / mlx->win_x) / 0.01f);
		mlx->duck.plane.xoffset -= mlx->duck.plane.xmouse_w - ((float)(x / mlx->duck.plane.scale) + mlx->duck.plane.xoffset);
		mlx->duck.plane.yoffset -= mlx->duck.plane.ymouse_w - ((float)(y / mlx->duck.plane.scale) + mlx->duck.plane.yoffset);
	}
	else
		ft_printf("Mousething N.%d\n", keysym);
	plot_data(mlx);
	return (0);
}

int	handle_keypress(int keysym, t_mlx *mlx)
{
	float			rad;
	static int		file;

	rad = 1 * MY_PI / 180;

	if (keysym == 7) // temp mouse keysym == 1
	{
		mlx->setty.right_click = 1;
		//ft_printf("RIGHT CLICK!?!?\n");
		mlx_mouse_get_pos(mlx->win, &mlx->xmouse_s, &mlx->ymouse_s);
	}

	if (keysym == XK_Up || keysym == 126)
		mlx->duck.plane.r_x += -rad * 5;
	else if (keysym == XK_Down || keysym == 125)
		mlx->duck.plane.r_x += rad * 5;
	else if (keysym == XK_Right || keysym == 124)
		mlx->duck.plane.r_y += -rad * 5;
	else if (keysym == XK_Left || keysym == 123)
		mlx->duck.plane.r_y += rad * 5;
	else if (keysym == XK_a || keysym == 0)
		mlx->duck.plane.xoffset -= 10;
	else if (keysym == XK_d || keysym == 2)
		mlx->duck.plane.xoffset += 10;
	else if (keysym == XK_w || keysym == 13)
		mlx->duck.plane.yoffset -= 10;
	else if (keysym == XK_s || keysym == 1)
		mlx->duck.plane.yoffset += 10;
	else if (keysym == XK_equal || keysym == 24)
		mlx->setty.mana += 10.0f;
	else if (keysym == XK_minus || keysym == 27)
		mlx->setty.mana -= 10.0f;
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
		mlx->duck.plane.r_y = 0.0f;
		mlx->duck.plane.r_x = 0.0f;
		mlx->duck.plane.r_z = 0.0f;
		mlx->setty.sel_x = 1;
		mlx->setty.sel_y = 1;
		mlx->setty.sel_z = 1;
		mlx->duck.plane.xoffset = (MLX_WIN_X / 4.0f);
		mlx->duck.plane.yoffset = (MLX_WIN_Y / 1.3f);
		mlx->duck.plane.xmouse_w = 0;
		mlx->duck.plane.ymouse_w = 0;
		mlx->duck.plane.scale = 1.0f;
	}
	else if (keysym == XK_p || keysym == 35)
	{
		duck_free_obj_list(mlx->duck.live_objs, &free);
		ft_free_data_list(mlx->data.list, &free);
		mlx->duck.live_objs = NULL;
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
