/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_startup_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:32:01 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/12 16:12:46 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	juice_the_pc(char flag, char **argv, t_mlx *mlx);

/* default settings for mlx variables */
void	zed_startup_settings(char **argv, t_mlx *mlx)
{
	mlx->plane.r_z = 0 * MY_PI / 180;
	mlx->plane.r_x = 0 * MY_PI / 180;
	mlx->plane.r_y = 50 * MY_PI / 180;
	mlx->plane.origin.z = -100.0f;
	mlx->plane.origin.x = (MLX_WIN_X / 4.0f);
	mlx->plane.origin.y = (MLX_WIN_Y / 1.5f);
	mlx->plane.y_shift = 0;
	mlx->plane.fov = 1.0f;
	mlx->live_objs = NULL;
	mlx->data.list = NULL;
	mlx->data.obj_nb = 0;
	mlx->setty.sel_x = 1;
	mlx->setty.sel_y = 1;
	mlx->setty.sel_z = 1;
	mlx->setty.mana = 0;
	mlx->argv = argv;
}

void	fdf_startup_settings(char **argv, t_mlx *mlx)
{
	mlx->plane.r_z = 0 * MY_PI / 180;
	mlx->plane.r_x = 0 * MY_PI / 180;
	mlx->plane.r_y = 0 * MY_PI / 180;
	mlx->plane.origin.z = 0.0f;
	mlx->plane.origin.x = 30.0f;
	mlx->plane.origin.y = 30.0f;
	mlx->plane.y_shift = 0;
	mlx->plane.fov = 1.0f;
	mlx->live_objs = NULL;
	mlx->data.list = NULL;
	mlx->data.obj_nb = 0;
	mlx->data.max_x = 0;
	mlx->data.max_y = 0;
	mlx->setty.sel_x = 1;
	mlx->setty.sel_y = 1;
	mlx->setty.sel_z = 1;
	mlx->setty.mana = 0;
	mlx->argv = argv;
}

/*set up the pc-side of the t_data (mlx) struct
RETURNS: 0 all good, 1 error*/
int	juice_the_pc(char flag, char **argv, t_mlx *mlx)
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
	if (flag == ZED)
		zed_startup_settings(argv, mlx);
	else if (flag == FDF)
		fdf_startup_settings(argv, mlx);
	else
	{
		ft_printf("wrong flag [%i], moron\n", flag);
		clean_exit(mlx);
	}
	return (0);
}
