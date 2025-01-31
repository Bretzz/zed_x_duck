/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_startup_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:32:01 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/31 20:45:59 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	juice_the_pc(t_mlx *mlx);

/*set up the pc-side of the t_data (mlx) struct
RETURNS: 0 all good, 1 error*/
int	juice_the_pc(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win_x = MAX_WIN_X - 100;
	mlx->win_y = MAX_WIN_Y - 100;
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
	mlx->plane.r_z = 0 * MY_PI / 180; // the z axis orientation, 0 = towards the user
	mlx->plane.r_x = 0 * MY_PI / 180; // the z axis orientation, 0 = towards the user
	mlx->plane.r_y = 50 * MY_PI / 180;/* 60 * MY_PI / 180 */; // the z axis orientation, 0 = towards the user
	mlx->plane.origin.z = -100.0f;
	mlx->plane.origin.x = (MAX_WIN_X / 4.0f) /* - (MAX_WIN_X / 4.0f) */;
	mlx->plane.origin.y = (MAX_WIN_Y / 1.5f) /* + (MAX_WIN_Y / 8.0f) */;
	mlx->plane.y_shift = 0;
	mlx->plane.fov = 1.0f;
	mlx->live_points = NULL;
	return (0);
}
