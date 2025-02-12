/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_startup_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:32:01 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/12 18:57:56 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	juice_the_pc(char **argv, t_mlx *mlx);

/* default settings for mlx variables */
void	startup_settings(char **argv, t_mlx *mlx)
{
	mlx->plane.r_z = 0 * MY_PI / 180;
	mlx->plane.r_x = 0 * MY_PI / 180;
	mlx->plane.r_y = 50 * MY_PI / 180;
	mlx->plane.origin.z = -100.0f;
	mlx->plane.origin.x = (MAX_WIN_X / 4.0f);
	mlx->plane.origin.y = (MAX_WIN_Y / 1.5f);
	mlx->plane.y_shift = 0;
	mlx->plane.fov = 1.0f;
	mlx->live_objs = NULL;
	mlx->data.list = NULL;
	mlx->data.obj_nb = 0;
	mlx->max_threads = 16;
	mlx->setty.sel_x = 1;
	mlx->setty.sel_y = 1;
	mlx->setty.sel_z = 1;
	mlx->setty.mana = 0;
	mlx->argv = argv;
}

/*set up the pc-side of the t_data (mlx) struct
RETURNS: 0 all good, 1 error*/
int	juice_the_pc(char **argv, t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win_x = MAX_WIN_X;
	mlx->win_y = MAX_WIN_Y;
	mlx->win = mlx_new_window(mlx->mlx, mlx->win_x, mlx->win_y, "print_zed");
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
	startup_settings(argv, mlx);
	return (0);
}
