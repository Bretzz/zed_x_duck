/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duck_engine.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 03:41:11 by totommi           #+#    #+#             */
/*   Updated: 2025/02/18 02:50:26 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* the core idea is that you fill a data.list or a data.arr with points,
then you create the objects out of that points and you assign them to
duck->live_objects. Then you put them to screen. */

#ifndef DUCK_ENGINE_H
# define DUCK_ENGINE_H

# ifndef MAX_THREADS
#  define MAX_THREADS 4
# endif

# define AXIS 0 /* Axis object tag */
# define DATA 1 /* Data plot tag */

# define MY_PI 3.14159265359

# include "minilibft.h"
# include <math.h>
# include <pthread.h>

#include <stdio.h>

//screen space point
typedef struct s_pixel
{
	int		x;
	int		y;
}				t_pixel;

//world space point
typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}				t_point;

//world space point list
typedef struct s_point_list
{
	t_point 			point;
	unsigned int		color;
	float				data;
	struct s_point_list	*tail;
	struct s_point_list	*next;
}				t_point_list;

//signle object made of multiple world points
typedef struct s_obj_list
{
	unsigned int		tag;
	t_point				origin;
	void				*data;
	t_point_list		*points;
	t_point_list		*points_tail;
	struct s_obj_list	*obj_tail;
	struct s_obj_list	*next_obj;
}				t_obj_list;

//data of the world space (plane)
typedef struct s_plane
{
	float		xoffset;	//offset from the screen on the x-axis
	float		yoffset;	//offset from the screen on the y-axis
	float		r_x;		//rotation of the x axis (rad)
	float		r_y;		//rotation of the y axis (rad)
	float		r_z;		//rotation of the z axis (rad)
	float		scale;		//scale of the plane (starts from 1)
	float		xmouse_w;	//mouse x world coordinate
	float		ymouse_w;	//mouse y world coordinate
}				t_plane;

//all data wrapper
typedef struct s_duck
{
	unsigned int	obj_nb;
	t_point			centre;
	t_plane			plane;
	t_obj_list		*live_objs;
	void			*mlx;	//bigger mlx struct
}				t_duck;

//list for multithreading :D
typedef struct s_pid_lst
{
	pthread_t			pid;
	unsigned int		layer;
	int					(*exclude)(void *, t_obj_list *);
	void 				(*pixel_put)(void *, int, int, float, unsigned int);
	t_obj_list			*obj;
	t_duck				*duck;
	struct s_pid_lst	*next;
}				t_pid_lst;

/* POINT_MASETERS */

void	put_point(t_point p, int color, void (*pixel_put)(void *, int, int, float, unsigned int), t_duck *duck);
t_point	rotate_point(t_point p, t_point c, t_duck *duck);

/* SHAPEMAKERS */

//base shape makers, add the points to the last obj (require an obj to be initialized)
int		fill_line(t_point a, t_point b, int color, t_duck *duck);
int		fill_area(t_point a, t_point b, t_point c, int color, t_duck *duck);


//example of use for fill_line and fill_area (already create their obj)
int		point_to_rombus(t_point p, void *data, int color, t_duck *duck);
int		point_to_cross(t_point p, void *data, int color , t_duck *duck);

/* POINTS-TO-SCREEN */

//put all the duck->live_objects to the screen
void	put_obj(t_obj_list *obj, t_duck *duck, int (*exclude)(void *, t_obj_list *), void (*pixel_put)(void *, int, int, float, unsigned int));
void	put_data(t_duck *duck, int (*exclude)(void *, t_obj_list *), void (*pixel_put)(void *, int, int, float, unsigned int));
void	put_data_thread(t_duck *duck, int (*exclude)(void *, t_obj_list *), void (*pixel_put)(void *, int, int, float, unsigned int));

/* LIST-FUNCTIONS */

//obj_list and point_list utils
int		duck_objnew(t_obj_list **obj);
int		duck_pointail(t_point_list **list, int color, float data, t_point point);
int		duck_point_to_obj_tail(t_obj_list *obj_tail, int color, void *data, t_point point);
t_point	get_list_centre(t_point_list *list, int pt_num);


//pid_list utils
t_pid_lst	*duck_pidnew(pthread_t pid);
int			duck_pid_tail(t_pid_lst **list, t_pid_lst **tail, t_pid_lst *node);
int			duck_pidnew_tail(t_pid_lst **list, t_pid_lst **tail, pthread_t pid);

/* MATH FUNCTIONS */

int		ft_isuint(const char *s);
int		ft_isfloat(const char *s);
int		ft_isfloat_space(const char *s);
float	ft_atof(const char *nptr); //invalid reads on "decimal." numbers, eg: "123."
int		ft_atohexi(const char *nptr);

float	ft_absf(float f);
float	ft_distf(t_point a, t_point b);
int		point_equal(t_point a, t_point b);
t_point	any_not_obtuse(t_point a, t_point b, t_point c);

float	ft_anglef(t_point a, t_point o, t_point b);
float	ft_areaf(t_point a, t_point b, t_point c);
int		is_inside(t_point p, t_point a, t_point b, t_point c);

/* FREE_STUFF */

void	ft_free_arr(char **arr);
void	duck_free_point_list(t_point_list *list);
void	duck_free_obj_list(t_obj_list *obj, void (*del)(void *));
void	duck_free_pid_lst(t_pid_lst **list);

#endif