/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:54:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/02 14:41:35 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	my_pixel_put(t_mlx *mlx, int x, int y, float z, int color);
void	put_point(t_point p, int color, t_mlx *mlx);
void	plot_data(t_mlx *mlx);

/* we should be taking into accounnt the depth of the point,
but we're not handling black points priority. */
void	my_pixel_put(t_mlx *mlx, int x, int y, float z, int color)
{
	char	*dst;
	float	*z_dest;
	
//	printf("putting2: [%i, %i]:%f\n", x, y, z);
	dst = mlx->img->addr + (y * mlx->img->line_length + x * (mlx->img->bits_per_pixel / sizeof(int *)));
	z_dest = mlx->z_img + (y * mlx->img->line_length + x * (mlx->img->bits_per_pixel / sizeof(float *)));
	if (*dst != 0x0 && *z_dest > z)
		return ;
	*(unsigned int *)dst = color;
	*(float *)z_dest = z;
}

void	rotate_list(t_point_list *list, t_point centre, t_mlx *mlx)
{
	while (list != NULL)
	{
		//printf("rotating (%f, %f, %f)\n", list->point.x, list->point.y, list->point.z);
		list->point = rotate_point(list->point, centre, mlx);
		list = list->next;
	}
}

void	put_data(t_mlx *mlx)
{
	t_obj_list		*obj;
	t_point_list	*list;
	//unsigned int	shaded;

	obj = mlx->live_objs;
	while (obj != NULL)
	{
		//shaded = blend_colors(mlx->live_objs->points->color, 0x000000, 32);
		if ((obj->tag == DATA && ((mlx->setty.sel_y <= 0 && (obj->origin.y == mlx->setty.sel_y))
			|| (mlx->setty.sel_x > 0 && mlx->setty.sel_y > 0 && mlx->setty.sel_z > 0))
			&& (mlx->setty.mana <= 0 || obj->obj_value > mlx->setty.mana))
			|| obj->tag != DATA)
		{
			list = obj->points;
			while (list != NULL)
			{
				//list->point = rotate_point(list->point, mlx->data.centre, mlx);
		//		printf("putting: (%f, %f, %f)\n", list->point.x, list->point.y, list->point.z);
				//printf("value=%f, setty.mana=%f\n", obj->obj_value, mlx->setty.mana);
				/* if (mlx->setty.mana > 0 && obj->obj_value <= mlx->setty.mana)
					put_point(list->point, shaded, mlx);
				else if (mlx->setty.mana <= 0 || obj->obj_value > mlx->setty.mana) */
				put_point(list->point, list->color, mlx);
				/* else
					put_point(list->point, blended, mlx); */
				list = list->next;
			}
		}
		obj = obj->next_obj;
	}
}

void	plot_data(t_mlx *mlx)
{
	t_point a;

	(*mlx).img->img = mlx_new_image((*mlx).mlx, (*mlx).win_x, (*mlx).win_y);
	(*mlx).img->addr = mlx_get_data_addr((*mlx).img->img, &(*mlx).img
			->bits_per_pixel, &(*mlx).img->line_length, &(*mlx).img->endian);
	mlx->z_img = (float *)malloc(mlx->win_y * mlx->img->line_length * mlx->img->bits_per_pixel * sizeof(float));
	if (!mlx->img->img || !mlx->img->addr || !mlx->z_img)
		return ;

	//point_to_rombus(a, 356, mlx);
	put_data(mlx);

	//printf("ORIGIN: (%f, %f, %f)\n", mlx->plane.origin.x, mlx->plane.origin.y, mlx->plane.origin.z);
	to_zero(&a);
	put_point(a, 0x00FFFF, mlx);
	my_pixel_put(mlx, mlx->plane.origin.x, mlx->plane.origin.y, mlx->plane.origin.z, 0xFF0000); //RED
//	put_point(a, 0x00FFFF, mlx); //YELLOW?
//	put_point(b, 0x00FFFF, mlx); //YELLOW?
//	put_point(c, 0x00FFFF, mlx); //YELLOW?
	mlx_put_image_to_window((*mlx).mlx, (*mlx).win, (*mlx).img->img, 0, 0);
	mlx_destroy_image((*mlx).mlx, (*mlx).img->img);
	free(mlx->z_img);
	mlx->z_img = NULL;
}

/* this function does the magic.
if you pass a (1, 1, 1), it returns the equivalent in the axis we just plot
(actually just swaps the y coordinate :D) */
// VOLUME -- Xmin: 6000 -- Xmax: 6800
// VOLUME -- Ymin: 2800 -- Ymax: 4000
// VOLUME -- Zmin: -1400 -- Zmax: -800
t_point	norm(t_point p)
{
	t_point	norm_p;

	norm_p.x = p.x - 6000;
	norm_p.y = (p.y + 1400) * -1;
	norm_p.z = p.z - 2800;
	return (norm_p);
}

/* takes an array of points as parameter.
fills the mlx->live points list with the shape you want to make from the point
RETURNS: the number of points added, -1 on error*/
int	data_birth(t_point_list *data, t_mlx *mlx)
{
	int	points;

	points = 0;
//	ft_printf("aaa\n");
	while (data != NULL)
	{
//		printf("bbb[%i]=(%f, %f, %f)\n", i, data->point.x, data->point.y, data->point.z);
		points += point_to_rombus(data->point, data->value, data->color, mlx);
		//points += point_to_cross(data->point, data->value, data->color, mlx);
//		ft_printf("ccc\n");
		data = data->next;
	}
	points += place_axis(555.0f, 555.0f, -600.0f, mlx);
//	rotate_list(mlx->live_points, mlx->data.centre, mlx);
	return (points);
}

/* Takes a path-string and mlx as parameters.
reads the file and appens a point with the coordinates
found in  "X       Y       Z" to mlx->data.list.*/
int	read_file(char *path, t_mlx *mlx)
{
	int		points;
	int		fd;
	char	*line;
	char	**split;
	t_point	p;
	t_point_list	*tail;

	fd = open(path, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if (!ft_strncmp("#DATE      HOUR          EPOCH               X       Y       Z         Vp     dVp     VpVs    dVpVs ", line, 100))
		{
			free(line);
			break ;
		}
		free(line);
	}
	points = 0;
	while (points <= 11000 && (line = get_next_line(fd)))
	{
		split = ft_split(line, ' ');
		if (split == NULL)
			return (0);
		p.x = ft_atoi(split[3]);
		p.y = ft_atoi(split[5]);
		p.z = ft_atoi(split[4]);
		ft_lstadd_point_tail(&mlx->data.list, &tail, 0xcc0001, (ft_atof(split[7]) / 100), norm(p));
		//printf("adding: (%f, %f, %f)\n", p.x, p.y, p.z);
		ft_free_arr(split);
		free(line);
		points++;
		//break ;
	}
	return (points);
}

int	get_data(char **argv, int file, t_mlx *mlx)
{
	int		i;
	int		points;
	char	**paths;
	t_point			p;
	t_point_list	*tail;
	
	UNUSED(argv); UNUSED(paths); UNUSED(tail); UNUSED(p); UNUSED(i);
	/* to_zero(&p);
	i = 0;
	points = 1;
	while (i < points)
	{
		p.x = 6000 + (float)rand()/(float)(RAND_MAX/800);
		p.y = (800 + (float)rand()/(float)(RAND_MAX/400)) * -1;
		p.z = 2800 + (float)rand()/(float)(RAND_MAX/1200);
		printf("rand[%i]: (%f,%f,%f)\n", i, p.x, p.y, p.z);
		ft_lstadd_point_tail(&mlx->data.list, &tail, 0xcc0001, 128, norm(p));
		i++;
	} */
	ft_printf("data found??\n");
	paths = ft_split(argv[1], ' ');
	ft_printf("%s...?\n", paths[file]);
	points = read_file(paths[file], mlx);
	if (!points)
	{
		ft_printf("no data found!!!\n");
		return (0);
	}
	ft_free_arr(paths);
	mlx->data.centre = get_list_centre(mlx->data.list, points);

	printf("centre=(%f, %f, %f)\n", mlx->data.centre.x, mlx->data.centre.y, mlx->data.centre.z);
	ft_printf("data generation complete\n");
	ft_printf("%i points added\n", data_birth(mlx->data.list, mlx));
	return (1);
}

int	main(int argc, char *argv[])
{
	t_mlx	*mlx;
	
	(void)argc; (void)argv;
	mlx = (t_mlx *)malloc(1 * sizeof(t_mlx));
	if (juice_the_pc(argv, mlx))
	{
		free(mlx);
		return (1);
	}
	ft_printf("PC JUICED!\n");
//	ft_printf("%s\n", argv[1]);
	/* if (!data_parser(argv[1]))
	{
		clean_exit(mlx);
		return (1);
	}
	else
		ft_printf("ALL GOOD\n"); */
	if (!get_data(argv, 0, mlx))
		return (1);
	clock_t t; 
	t = clock(); 
	plot_data(mlx);
	t = clock() - t; 
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
	printf("PLOT_DATA took %f seconds to execute \n", time_taken); 
	mlx_mouse_hook(mlx->win, &handle_mouse, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, &clean_exit, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, &clean_exit, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}

