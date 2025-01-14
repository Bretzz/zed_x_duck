/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:47:59 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/14 23:14:27 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

/*mlx and mlx->img are manually mallocated so we must manually free them
mlx->win and mlx->mlx are cleaned with built-in functions
(somehow mlx->mlx also needs to be freed manually)*/
int	clean_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	if (mlx->img)
		free(mlx->img);
	free(mlx->mlx);
	free(mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

/* 4 = UP, 5 = DOWN*/
int	handle_mouse(int keysym, int x, int y, t_mlx *mlx)
{
	UNUSED(x); UNUSED(y); UNUSED(mlx);
	ft_printf("Mousething N.%d\n", keysym);
	return (0);
}

int	handle_keypress(int keysym, t_mlx *mlx)
{
	if (keysym == 65307)
	{
		clean_exit(mlx);
		return (0);
	}
	ft_printf("Keypress: %d\n", keysym);
	return (0);
}
