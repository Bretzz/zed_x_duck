/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_zed_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:43:21 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/18 15:39:42 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	get_zed_data(char **argv, int file, t_mlx *mlx);
int	zed_data_birth(t_data_list *data, int file_num, t_mlx *mlx);
t_point	zed_norm(t_point p);

unsigned int zed_color(float measrd, float error, float *val_lim, float *err_lim)
{
	float			val_mid;
	float			range;
	float			sat;
	float			value;
	unsigned int	hue;
	
	(void)error; (void)err_lim;
	val_mid = 2.5f/* (val_lim[1] + (val_lim[0] - val_lim[1]) / 2) / 1000 */;
	range = 5/* (val_lim[0] - val_lim[1]) / 1000 */;
	printf("mid=%f, val=%f, [1]=%f, range=%f\n", val_mid, measrd, val_lim[1], range);
	if (measrd < val_mid - (range / 4))
		hue = 240/* + (float)(measrd / ( val_lim[0] - val_lim[1])) * 60 */;	//blue
	else if (measrd < val_mid)
		hue = 120/* + (float)(measrd / ( val_lim[0] - val_lim[1])) * 60 */;	//green
	else if (measrd < val_mid + (range / 4))
		hue = 60/* + (float)(measrd / ( val_lim[0] - val_lim[1])) * 60 */;	//yellow
	else
		hue = 0/* (float)(measrd / ( val_lim[0] - val_lim[1])) * 6 */;		//red
	sat = 1;
	value = 1/* 0.35 + (1 - (float)((error)/ (err_lim[0] - err_lim[1]))) * 0.65 */; //poco chiaro
	return (hsv_to_rgb(hue, sat, value));
//	printf("color=%x\n", color);
//	printf("measrd=%f, error=%f\n", measrd, error);
//	printf("hue=%u, sat=%f, value=%f\n", hue, sat, value);
	//return (color);
}

/* this function does the magic.
if you pass a (1, 1, 1), it returns the equivalent in the axis we just plot
(actually just swaps the y coordinate :D) */
// VOLUME -- Xmin: 6000 -- Xmax: 6800
// VOLUME -- Ymin: 2800 -- Ymax: 4000
// VOLUME -- Zmin: -1400 -- Zmax: -800
t_point	zed_norm(t_point p)
{
	t_point	norm_p;

	//norm_p.x = ((p.x - 6000) / 800) * mlx->win_x - 100;
	norm_p.x = (p.x - 6000);
	norm_p.y = (p.y + 1400) * -1;
	norm_p.z = p.z - 2800;
	return (norm_p);
}

/* takes an array of points as parameter.
fills the mlx->live points list with the shape you want to make from the point
RETURNS: the number of points added, -1 on error*/
int	zed_data_birth(t_data_list *data, int file_num, t_mlx *mlx)
{
	t_values	*values;
	int	points;

	points = 0;
	mlx->duck.obj_nb = 0;
	if (file_num == 0)
		mlx->setty.mana = mlx->data.err_lim[0];
	while (data != NULL)
	{
		//printf("bbb[%i]=(%f, %f, %f)\n", mlx->duck.obj_nb, data->point.x, data->point.y, data->point.z);
		values = (t_values *)data->values;
		values->measrd = (((values->measrd - mlx->data.val_lim[1]) / (mlx->data.val_lim[0] - mlx->data.val_lim[1])) * 5);
		//points += my_point_to_rombus(data->point, values, zed_color(values->measrd, values->error, mlx->data.val_lim, mlx->data.err_lim), &mlx->duck);
		points += my_point_to_sphere(data->point, values, zed_color(values->measrd, values->error, mlx->data.val_lim, mlx->data.err_lim), &mlx->duck);
		//points += my_point_to_cross(data->point, values, zed_color(values->measrd, values->error, mlx->data.val_lim, mlx->data.err_lim), &mlx->duck);
		//points += point_to_cross(data->point, data->value, data->color, mlx);
//		ft_printf("ccc\n");
		data = data->next;
		mlx->duck.obj_nb++;
		//break ;
	}
	//points += place_axis(555.0f, 555.0f, -600.0f, mlx);
//	rotate_list(mlx->live_points, mlx->data.centre, mlx);
	return (points);
}

/* Funcions that fills the mlx->data list. */

/* takes a path string as parameter.
reads the file passed (zed dataa formatted file expected)
until the header is found.
RETURNS: 1 all good, 0 on error. */
int	skip_header(int fd)
{
	char	*line;
	
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

/* takes a char pointer as parameter.
takes all the data it wants and adds them to the mlx->data.list.
RETURNS: 1 all ok, 0 error. */
int	read_zed_line(char *line, t_data_list **tail, t_mlx *mlx)
{
	t_point		p;
	t_values	*values;
	char		**split;
	
	values = (t_values *)malloc(1 * sizeof(t_values));
	if (!values)
		return (0);
	split = ft_split(line, ' ');
	if (split == NULL)
	{
		free(values);
		return (0);
	}
	p.x = ft_atoi(split[3]);
	p.y = ft_atoi(split[5]);
	p.z = ft_atoi(split[4]);
	values->measrd = ft_atof(split[6]);
	values->error = ft_atof(split[7]);
	ft_datalst_add_tail(&mlx->data.list, tail, values, zed_norm(p));
	if (values->measrd > mlx->data.val_lim[0])
		mlx->data.val_lim[0] = values->measrd;
	if (values->measrd < mlx->data.val_lim[1])
		mlx->data.val_lim[1] = values->measrd;
	if (values->error > mlx->data.err_lim[0])
		mlx->data.err_lim[0] = values->error;
	if (values->error < mlx->data.err_lim[1])
		mlx->data.err_lim[1] = values->error;
	//printf("adding: (%f, %f, %f)\n", p.x, p.y, p.z);
	ft_free_arr(split);
	return (1);
}

/* Takes a path-string and mlx as parameters.
reads the file and appens a point with the coordinates
found in  "X       Y       Z" to mlx->data.list.*/
int	read_zed_file(char *path, t_mlx *mlx)
{
	int				fd;
	char			*line;
	t_data_list		*tail;
	unsigned int	points;

	fd = open(path, O_RDONLY);
	if (!skip_header(fd))
		return (0);
	points = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!read_zed_line(line, &tail, mlx))
		{
			free(line);
			return (0);
		}
		free(line);
		points++;
	}
	close(fd);
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
	mlx->duck.centre = get_data_list_centre(mlx->data.list, points);
	printf("centre=(%f, %f, %f)\n", mlx->duck.centre.x, mlx->duck.centre.y, mlx->duck.centre.z);
	ft_printf("data generation complete\n");
	ft_printf("%i points added\n", zed_data_birth(mlx->data.list, file, mlx));
	return (1);
}
