/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_startup_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:32:01 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/14 23:19:17 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

/*set up the pc-side of the t_data (mlx) struct
RETURNS: 0 all good, 1 error*/
int	juice_the_pc(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win_x = 1920;
	mlx->win_y = 1080;
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
	return (0);
}
