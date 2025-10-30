/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checky_funtions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:26:33 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/14 17:47:59 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"
void	ft_print_point_arr(t_point **arr, int max_x);

void	ft_print_point_arr(t_point **arr, int max_x)
{
	int	x;
	int	y;

	y = 0;
	while (arr[y] != NULL)
	{
		x = 0;
		while (x < max_x)
		{
			ft_printf("%i ", (int)arr[y][x].z);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

