/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:54:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/19 13:44:56 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	my_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/* takes a char pointer as a parameter
RETURNS: 1 if the string begins with a 'date', 0 if it doesn't */
int	is_date(char *line)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (*line == '\0')
			return (0);
		if ((i == 4 || i == 7))
		{
			if (*line != '/')
			{
				ft_printf("date: backslash [%i] strike OUT\n", i);
				return (0);
			}
		}
		else if (!ft_isdigit(*line))
		{
			ft_printf("date: digit [%i] strike OUT\n", i);
			return (0);
		}
		line++;
		i++;
	}
	return (1);
}

/* takes a char pointer as a parameter
RETURNS: 1 if the string begins with a 'timestamp', 0 if it doesn't */
int	is_time(char *line)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (*line == '\0')
			return (0);
		if ((i == 2 || i == 5))
		{
			if (*line != ':')
			{
				ft_printf("time: colon [%i] strike OUT\n", i);
				return (0);
			}
		}
		else if (!ft_isdigit(*line))
		{
			ft_printf("time: digit [%i] strike OUT\n", i);
			return (0);
		}
		line++;
		i++;
	}
	return (1);
}

/* 2020/12/04 00:00:00      1607040000       6000.   4000.   -800.       5580.    430.    1.790    0.052
take a char pointer as a parameter
RETURNS: 1 if the line is formatted as the line above, 0 if it isn't */
int	line_parser(char *line)
{
	int	i;

	if (!line)
		return (0);
	if (!is_date(line))
		return (0);
	line += 10;
	if (*line != ' ')
		return (0);
	line++;
	if (!is_time(line))
		return (0);
	line += 8;
	i = 0;
	//ft_printf("date + time OK\n");
	while (i < 8)
	{
		if (*line == '\0' || *line != ' ')
			return (0);
		//ft_printf("element close correctly\n");
		while (*line && *line == ' ')
			line++;
		if (i > 0 && i <= 5 && i != 3)
		{
			while (*line && ft_isdigit(*line))
				line++;
			if (!*line || *line != '.')
				return (0);
			line++;
			//ft_printf("'digit.' element OK\n");
		}
		else if (i == 3)
		{
			if (!*line || *line != '-')
				return (0);
			line++;
			while (*line && ft_isdigit(*line))
				line++;
			if (!*line || *line != '.')
				return (0);
			line++;
			//ft_printf("'-digit.' element OK\n");
		}
		else if (i >= 6)
		{
			if (!ft_isfloat_space(line))
				return (0);
			while (*line && (ft_isdigit(*line) || *line == '.'))
				line++;
			//ft_printf("'float' element OK\n");
		}
		else
		{
			while (*line && ft_isdigit(*line))
				line++;
			//ft_printf("'digit' element OK\n");
		}
		i++;
		//if (i < 6 || (i > 16 && i < 23) || (i > 28 && i < 31) || (i > 36 && i < 39) || (i > 44 & i < 51) || ())
	}
	return (1);
}

/* #DATE      HOUR          EPOCH               X       Y       Z         Vp     dVp     VpVs    dVpVs 
takes a file descriptor as parameter 
Reads the file line by line until it matches the line above
RETURNS: 0 if all the lines after respect the syntax,
otherwhise returns the line (number) that dropped the error*/
int	file_parser(int fd)
{
	int		i;
	int		header;
	char	*line;
	
	header = 0;
	i = 1;
	while ((line = get_next_line(fd)))
	{
		if (!ft_strncmp("#DATE      HOUR          EPOCH               X       Y       Z         Vp     dVp     VpVs    dVpVs ", line, 100))
		{
			header = 1;
			free(line);
			i++;
			break ;
		}
		free(line);
		i++;
	}
	if (!header)
		return (i);
	while ((line = get_next_line(fd)))
	{
		if (!line_parser(line))
		{
			free(line);
			return (i);
		}
		free(line);
		i++;
	}
	return (0);
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

int	main(void)
{
	int		line;
	int	fd;
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(1 * sizeof(t_mlx));
	if (juice_the_pc(mlx))
	{
		free(mlx);
		return (1);
	}

	//line_parser(NULL);
	/* if (!is_date("2020/12/04 00:00:00      1607040000       6000.   4000.   -800.       5580.    430.    1.790    0.052"))
		ft_printf("not a date"); */
	fd = open("data/2020_12_04_00.elastic_model", O_RDONLY);
	if ((line = file_parser(fd)))
	{
		ft_printf("line [%i]: ", line);
		write(2, "file parse Error\n", 18);
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
