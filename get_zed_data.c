/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_zed_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:43:21 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/12 16:06:37 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	get_zed_data(char **argv, int file, t_mlx *mlx);

/* takes an array of points as parameter.
fills the mlx->live points list with the shape you want to make from the point
RETURNS: the number of points added, -1 on error*/
int	zed_data_birth(t_point_list *data, t_mlx *mlx)
{
	int	points;

	points = 0;
	mlx->data.obj_nb = 0;
	while (data != NULL)
	{
//		printf("bbb[%i]=(%f, %f, %f)\n", i, data->point.x, data->point.y, data->point.z);
		points += point_to_rombus(data->point, data->value, data->color, mlx);
		//points += point_to_cross(data->point, data->value, data->color, mlx);
//		ft_printf("ccc\n");
		data = data->next;
		mlx->data.obj_nb++;
	}
	points += place_axis(555.0f, 555.0f, -600.0f, mlx);
//	rotate_list(mlx->live_points, mlx->data.centre, mlx);
	return (points);
}

/* Funcions that fills the mlx->data list. */

/* takes a path string as parameter.
reads the file passed (zed dataa formatted file expected)
until the header is found.
RETURNS: 1 all good, 0 on error. */
int	skip_header(char *path)
{
	int		fd;
	char	*line;
	
	fd = open(path, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if (!ft_strncmp("#DATE      HOUR          EPOCH               \
X       Y       Z         Vp     dVp     VpVs    dVpVs ", line, 100))
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (1);
}

/* Takes a path-string and mlx as parameters.
reads the file and appens a point with the coordinates
found in  "X       Y       Z" to mlx->data.list.*/
int	read_zed_file(char *path, t_mlx *mlx)
{
	int		fd;
	char	*line;
	char	**split;
	t_point	p;
	t_point_list	*tail;
	unsigned int	points;

	if (!skip_header(path))
		return (0);
	fd = open(path, O_RDONLY);
	points = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		split = ft_split(line, ' ');
		if (split == NULL)
			return (0);
		p.x = ft_atoi(split[3]);
		p.y = ft_atoi(split[5]);
		p.z = ft_atoi(split[4]);
		ft_lstadd_point_tail(&mlx->data.list, &tail, 0xcc0001, (ft_atof(split[7]) / 100), zed_norm(p));
		//printf("adding: (%f, %f, %f)\n", p.x, p.y, p.z);
		ft_free_arr(split);
		free(line);
		points++;
	}
	return (points);
}

int	get_zed_data(char **argv, int file, t_mlx *mlx)
{
	int		points;
	char	**paths;
	
	ft_printf("data found??\n");
	paths = ft_split(argv[1], ' ');
	ft_printf("%s...?\n", paths[file]);
	points = read_zed_file(paths[file], mlx);
	if (!points)
	{
		ft_printf("no data found!!!\n");
		return (0);
	}
	ft_free_arr(paths);
	mlx->data.centre = get_list_centre(mlx->data.list, points);
	printf("centre=(%f, %f, %f)\n", mlx->data.centre.x, mlx->data.centre.y, mlx->data.centre.z);
	ft_printf("data generation complete\n");
	ft_printf("%i points added\n", zed_data_birth(mlx->data.list, mlx));
	return (1);
}
