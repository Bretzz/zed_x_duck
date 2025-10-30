/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_startup_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:32:01 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/18 04:00:52 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	juice_the_pc(char **argv, t_mlx *mlx);

/* default settings for mlx variables */
void	zed_startup_settings(char **argv, t_mlx *mlx)
{
	mlx->setty.right_click = 0;
	mlx->duck.plane.r_z = 0 * MY_PI / 180;
	mlx->duck.plane.r_x = 0 * MY_PI / 180;
	mlx->duck.plane.r_y = 50 * MY_PI / 180;
	mlx->duck.plane.xoffset = (MLX_WIN_X / 4.0f);
	mlx->duck.plane.yoffset = (MLX_WIN_Y / 1.3f);
	mlx->duck.plane.scale = 1.0f;
	mlx->duck.plane.xmouse_w = 0;
	mlx->duck.plane.ymouse_w = 0;
	mlx->duck.live_objs = NULL;
	mlx->duck.obj_nb = 0;
	mlx->data.list = NULL;
	mlx->data.val_lim[0] = FLT_MIN;
	mlx->data.val_lim[1] = FLT_MAX;
	mlx->data.err_lim[0] = FLT_MIN;
	mlx->data.err_lim[1] = FLT_MAX;
	mlx->setty.sel_x = 1;
	mlx->setty.sel_y = 1;
	mlx->setty.sel_z = 1;
	mlx->setty.mana = 0;
	mlx->argv = argv;
	mlx->duck.mlx = mlx;
}

/*set up the pc-side of the t_data (mlx) struct
RETURNS: 0 all good, 1 error*/
int	juice_the_pc(char **argv, t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win_x = MLX_WIN_X;
	mlx->win_y = MLX_WIN_Y;
	mlx->win = mlx_new_window(mlx->mlx, MLX_WIN_X, MLX_WIN_Y, "print_zed");
	if (!mlx->win)
	{
		free(mlx->mlx);
		return (1);
	}
	mlx->img = (t_img *)malloc(sizeof(t_img));
	if (!mlx->mlx)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		free(mlx->mlx);
		return (1);
	}
	zed_startup_settings(argv, mlx);
	return (0);
}
