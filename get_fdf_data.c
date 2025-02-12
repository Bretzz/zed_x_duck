/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fdf_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:13:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/13 00:09:20 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	get_fdf_data(char **argv, t_mlx *mlx);

void	get_friends(t_point *friend, int x, int y, t_mlx *mlx)
{
	t_point max;

	max.x = mlx->data.max_x;
	max.y = mlx->data.max_y;
	max.z = 0;

	max = fdf_norm(max);
	//printf("max_x=%f, max_y=%f\n", max.x, max.y);
	if (y > 0)
		friend[0] = mlx->data.arr[y - 1][x];
	else
		friend[0].x = -1;
	//ft_printf("got 0\n");
	if (y < mlx->data.max_y)
		friend[1] = mlx->data.arr[y + 1][x];
	else
		friend[1].x = -1;
	//ft_printf("got 1\n");
	if (x > 0)
		friend[2] = mlx->data.arr[y][x - 1];
	else
		friend[2].x = -1;
	//ft_printf("got 2\n");
	if (x < mlx->data.max_x)
		friend[3] = mlx->data.arr[y][x + 1];
	else
		friend[3].x = -1;
	//ft_printf("got 3\n");
}

int	link_friends(t_point point, t_point *friends, t_mlx *mlx)
{
	int	i;
	int	points = 0;

	//ft_printf("point=[%i,%i,%i]\n", (int)point.x, (int)point.y, (int)point.z);
	i = 0;
	if (!ft_lstnew_obj(&mlx->live_objs))
		return (-1);
	mlx->data.obj_nb++;
	//ft_printf("new SPIDER obj created!\n");
	while (i < 4)
	{
		//ft_printf("friend[%i]=[%i,%i,%i]\n", i, (int)friends[i].x, (int)friends[i].y, (int)friends[i].z);
		if (friends[i].x > 0)
		{
			/* if (!ft_lstnew_obj(&mlx->live_objs))
				return (-1);
			mlx->data.obj_nb++; */
			points += fill_line(point, friends[i], 0xcc0001, mlx);
		}
		i++;
	}
	return (points);
}

/* takes an array of points as parameter.
fills the mlx->live points list with the lines linkings the points
RETURNS: the number of points added, -1 on error*/
int	fdf_data_birth(t_point **data, t_mlx *mlx)
{
	int		x;
	int		y;
	int		points;
	t_point *friends; //up down left right

	/* (void)x; (void)y; (void)friends; (void)data; */
	friends = (t_point *)malloc(4 * sizeof(t_point));
	if (!friends)
		return (0);
	mlx->data.obj_nb = 0;
	points = 0;
	printf("max_x=%f, max_y=%f\n", mlx->data.max_x, mlx->data.max_y);
	y = 0;
	while (y <= mlx->data.max_y)
	{
		x = 0;
		while (x <= mlx->data.max_x)
		{
			//printf("linking [%f, %f, %f]\n", data[y][x].x, data[y][x].y, data[y][x].z);
			get_friends(friends, x, y, mlx);
			//ft_printf("got friends\n");
			points += link_friends(data[y][x], friends, mlx);
			x++;
		}
		y++;
	}
	//points += place_axis(555.0f, 555.0f, -600.0f, mlx);
//	rotate_list(mlx->live_points, mlx->data.centre, mlx);
	free(friends);
	return (points);
}

int	read_fdf_file(char *path, t_mlx *mlx)
{
	int		line_x;
	int		line_y;
	int		fd;
	char	*line;
	char	**split;
	t_point	p;
	t_point_list	*tail;

	fd = open(path, O_RDONLY);
	mlx->data.obj_nb = 0;
	line_y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		//ft_printf("line[%i]: %s", line_y, line);
		split = ft_split(line, ' ');
		if (split == NULL)
			return (0);
		line_x = 0;
		while (split[line_x] != NULL)
		{
			p.x = line_x;
			p.y = line_y;
			p.z = ft_atoi(split[line_x]);
			ft_lstadd_point_tail(&mlx->data.list, &tail, 0xcc0001, (2.0f), fdf_norm(p));
			if (p.x > mlx->data.max_x)
				mlx->data.max_x = p.x;
			if (p.y > mlx->data.max_y)
				mlx->data.max_y = p.y;
			line_x++;
		}
		//printf("adding: (%f, %f, %f)\n", p.x, p.y, p.z);
		ft_free_arr(split);
		free(line);
		mlx->data.obj_nb++;
		line_y++;
	}
	return (mlx->data.obj_nb);
}

int	get_fdf_data(char **argv, t_mlx *mlx)
{
	int		x;
	int		y;
	int		points;
	t_point_list	*data_list;
	
	ft_printf("fdf data found??\npath=%s\n", argv[1]);
	points = read_fdf_file(argv[1], mlx);
	if (!points)
	{
		ft_printf("no data found!!!\n");
		return (0);
	}
	mlx->data.arr = (t_point **)malloc((mlx->data.max_y + 2) * sizeof(t_point *));
	if (!mlx->data.arr)
	{
		//free mlx->data->list
		return (0);
	}
	mlx->data.arr[(int)mlx->data.max_y + 1] = NULL;
	data_list = mlx->data.list;
	y = 0;
	while (data_list != NULL)
	{
		mlx->data.arr[y] = (t_point *)malloc((mlx->data.max_x + 1) * sizeof(t_point));
		if (!mlx->data.arr[y])
		{
			//free_arr up to y
			return (0);
		}
		x = 0;
		while (data_list && x < mlx->data.max_x + 1)
		{
			mlx->data.arr[y][x] = data_list->point;
			//printf("[%f, %f, %f]\n", mlx->data.arr[y][x].x, mlx->data.arr[y][x].y, mlx->data.arr[y][x].z);
			data_list = data_list->next;
			x++;
		}
		y++;
	}
	printf("max_x=%f, max_y=%f\n", mlx->data.max_x, mlx->data.max_y);
	ft_print_point_arr(mlx->data.arr, mlx->data.max_x + 1);
	mlx->data.centre = get_list_centre(mlx->data.list, points);
	printf("centre=(%f, %f, %f)\n", mlx->data.centre.x, mlx->data.centre.y, mlx->data.centre.z);
	ft_printf("data generation complete\n");
	ft_printf("%i points added\n", fdf_data_birth(mlx->data.arr, mlx));
	//usleep(10000000);
	return (1);
}
