/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fdf_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:13:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/13 15:34:49 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	get_fdf_data(char **argv, t_mlx *mlx);
int	fdf_data_birth(t_point **data, t_mlx *mlx);
t_point	**list_to_arr(t_point_list *list, size_t max_x, size_t max_y);

/* RED=0xff0000, BLUE=0x0000ff. white=0xffffff*/
unsigned int	fdf_color(t_point p, float min_z, float max_z, int max_y)
{
	//float			scaled_z;
	float			hue;
	float			sat;
	float			value;
	unsigned int	color;
	unsigned int	plane_layer;
	float	artic_circle;
	unsigned int	antartic_circle;

	(void)min_z; (void)max_z; (void)p; (void)antartic_circle;
	color = 0x000000;

	plane_layer = max_z / 3.75;
	artic_circle = (2 * max_y) * 0.065377417342483;
	antartic_circle = (2 * max_y) * 0.183661521204891;
	//printf("artic_circle=%f\n", artic_circle);

	if (p.z < 0) //mare
	{
		hue = 240;  //blueish
		//scale on hsv blue
		sat = 0.75 + (float)(p.z / min_z) * 0.25;
		value = 1 - ((float)(p.z / min_z));
		color = hsv_to_rgb(hue, sat, value);
	}	
	else if (p.z < plane_layer) //pianura
	{
		hue = 80;  //greenish
		sat = 0.5 + (float)(p.z / (plane_layer)) * 0.5;
		value = (1 - (float)(p.z / (plane_layer)));
		color = hsv_to_rgb(hue, sat, value);
	}
	else //montagna
	{
		if ((p.y < artic_circle || p.y > max_y - antartic_circle)
			|| p.z > (8 * max_z) / 10)
		{
			hue = 195; //snowish
			sat = 0/* 0.80 + (float)(p.z / max_z) * 0.20 */;
			value = 0.95 + (float)(p.z / max_z) * 0.05;
		}
		else
		{
			hue = 30;  //brownish
			sat = 0.25 + (float)(p.z / max_z) * 0.75;
			value = (1 - (float)(p.z / max_z));
		}
		color = hsv_to_rgb(hue, sat, value);
	}
	return ((unsigned int)(color));
}

void	get_friends(t_point *friend, int x, int y, t_mlx *mlx)
{
	if (y < mlx->data.max_y)
		friend[0] = mlx->data.arr[y + 1][x];
	else
		friend[0].x = -1;
	if (x < mlx->data.max_x)
		friend[1] = mlx->data.arr[y][x + 1];
	else
		friend[1].x = -1;
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
	while (i < 2)
	{
		//ft_printf("friend[%i]=[%i,%i,%i]\n", i, (int)friends[i].x, (int)friends[i].y, (int)friends[i].z);
		if (friends[i].x >= 0)
		{
			/* if (!ft_lstnew_obj(&mlx->live_objs))
				return (-1);
			mlx->data.obj_nb++; */
			points += fill_line(fdf_norm(point, mlx), fdf_norm(friends[i], mlx), fdf_color(point, mlx->data.min_z, mlx->data.max_z, mlx->data.max_y), mlx);
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
	t_point *friends; //down right

	/* (void)x; (void)y; (void)friends; (void)data; */
	friends = (t_point *)malloc(2 * sizeof(t_point));
	if (!friends)
		return (0);
	mlx->data.obj_nb = 0;
	points = 0;
	printf("max_x=%f, max_y=%f, max_z=%f, min_z=%f\n", mlx->data.max_x, mlx->data.max_y, mlx->data.max_z, mlx->data.min_z);
	y = 0;
	while (y <= mlx->data.max_y)
	{
		x = 0;
		while (x <= mlx->data.max_x)
		{
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
	unsigned int	points;

	fd = open(path, O_RDONLY);
	points = 0;
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
			p.z = ft_atohexi(split[line_x]);
			ft_lstadd_point_tail(&mlx->data.list, &tail, 0xcc0001, (2.0f), p);
			if (p.x > mlx->data.max_x)
				mlx->data.max_x = p.x;
			if (p.y > mlx->data.max_y)
				mlx->data.max_y = p.y;
			if (p.z > mlx->data.max_z)
				mlx->data.max_z = p.z;
			if (p.z < mlx->data.min_z)
				mlx->data.min_z = p.z;
			line_x++;
			points++;
		}
		//printf("adding: (%f, %f, %f)\n", p.x, p.y, p.z);
		ft_free_arr(split);
		free(line);
		line_y++;
	}
	close(fd);
	return (points);
}

/* takes a list pointer, length of x, length of y as arameters.
RETURNS a mallocated int array with the element [y][x] has the value of
the z-value of the y * length_of_y + x element of the list. */
t_point	**list_to_arr(t_point_list *list, size_t max_x, size_t max_y)
{
	size_t	x;
	size_t	y;
	t_point	**arr;

	arr = (t_point **)malloc((max_y + 2) * sizeof(t_point *));
	if (!arr)
	{
		//free mlx->data->list
		return (NULL);
	}
	arr[(int)max_y + 1] = NULL;
	y = 0;
	while (list != NULL)
	{
		arr[y] = (t_point *)malloc((max_x + 1) * sizeof(t_point));
		if (!arr[y])
		{
			//free_arr up to y
			return (0);
		}
		x = 0;
		while (list && x < max_x + 1)
		{
			arr[y][x] = list->point;
			//printf("[%f, %f, %f]\n", arr[y][x].x, arr[y][x].y, arr[y][x].z);
			list = list->next;
			x++;
		}
		y++;
	}
	return (arr);
}

int	get_fdf_data(char **argv, t_mlx *mlx)
{
	// int		x;
	// int		y;
	int		points;
	// t_point_list	*data_list;
	
	ft_printf("fdf data found??\npath=%s\n", argv[1]);
	points = read_fdf_file(argv[1], mlx);
	if (!points)
	{
		ft_printf("no data found!!!\n");
		return (0);
	}
	ft_printf("got data\n");
	mlx->data.arr = list_to_arr(mlx->data.list, mlx->data.max_x, mlx->data.max_y);
	if (!mlx->data.arr)
		return (0);
	printf("max_x=%f, max_y=%f\n", mlx->data.max_x, mlx->data.max_y);
	ft_print_point_arr(mlx->data.arr, mlx->data.max_x + 1);
	mlx->data.centre = fdf_norm(get_list_centre(mlx->data.list, points), mlx);
	printf("centre=(%f, %f, %f)\n", mlx->data.centre.x, mlx->data.centre.y, mlx->data.centre.z);
	ft_printf("data generation complete\n");
	ft_printf("%i points added\n", fdf_data_birth(mlx->data.arr, mlx));
	//usleep(10000000);
	return (1);
}
