/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:54:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/22 03:13:57 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	my_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	plot_data(t_mlx *mlx)
{
	(*mlx).img->img = mlx_new_image((*mlx).mlx, (*mlx).win_x, (*mlx).win_y);
	(*mlx).img->addr = mlx_get_data_addr((*mlx).img->img, &(*mlx).img
			->bits_per_pixel, &(*mlx).img->line_length, &(*mlx).img->endian);

	my_pixel_put((*mlx).img, 1, 1, 0x0000FF00);

	mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img->img, 0, 0);
	mlx_destroy_image((*mlx).mlx, (*mlx).img->img);
}

int	main(int argc, char *argv[])
{
	char	*itoa;
	int		line;
	int		fd;
	t_mlx	*mlx;

	(void)argc;
	mlx = (t_mlx *)malloc(1 * sizeof(t_mlx));
	if (juice_the_pc(mlx))
	{
		free(mlx);
		return (1);
	}

	//line_parser(NULL);
	/* if (!is_date("2020/12/04 00:00:00      1607040000       6000.   4000.   -800.       5580.    430.    1.790    0.052"))
		ft_printf("not a date"); */
	if (ft_isfloat(argv[1]))
		ft_printf("FLOAT\n");
	else
		ft_printf("NOT FLOAT\n");
	printf("input=%f\n", ft_atof(argv[1]));
	printf("input=%f\n", (float)2.1);
	fd = open("data/2020_12_04_00.elastic_model", O_RDONLY);
	if ((line = file_parser(fd)))
	{
		(void)!write(1, "line [", 6);
		itoa = ft_itoa(line);
		(void)!write(1, itoa, ft_strlen(itoa));
		(void)!write(1, "]: file parse error\n", 21);
		free(itoa);
		clean_exit(mlx);
		return (1);
	}
	close(fd);
	plot_data(mlx);
	mlx_mouse_hook(mlx->win, &handle_mouse, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, &clean_exit, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
