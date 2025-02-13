/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 12:09:39 by topiana-          #+#    #+#             */
/*   Updated: 2024/12/21 19:14:16 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_ZED_H
# define PRINT_ZED_H

# ifndef MAX_THREADS
#  define MAX_THREADS 4
# endif

# define AXIS 0 /* Axis object tag */
# define DATA 1 /* Data plot tag */
# define ZED 122 /* ZED program behaviour flag */
# define FDF 102 /* FDF program behaviour flag */

# ifndef ESC_KEY
#  define ESC_KEY 65307
# endif

# ifndef MLX_WIN_X
#  define MLX_WIN_X 1920
# endif

# ifndef MLX_WIN_Y
#  define MLX_WIN_Y 1080
# endif

# define UNUSED(x) (void)(x)
# define MY_PI 3.14159265359

# include "mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
//# include <sys/stat.h>
# include <fcntl.h>
# include <pthread.h>

# include <stdio.h>
# include <time.h> 


typedef struct s_pixel
{
	int		z;
	int		x;
	int		y;
}				t_pixel;

typedef struct s_point
{
	float	z;
	float	x;
	float	y;
}				t_point;

typedef struct s_point_list
{
	t_point 		point;
	unsigned int	color;
	float			value;
	//struct s_point_list	close[4];
	struct s_point_list	*next;
}				t_point_list;

typedef struct s_obj_list
{
	unsigned int	tag;
	float			obj_value;
	t_point			origin;
	t_point_list	*points;
	t_point_list	*points_tail;
	struct s_obj_list	*obj_tail;
	struct s_obj_list	*next_obj;
}				t_obj_list;

typedef struct s_plane
{
	float		r_z;
	float		r_x;
	float		r_y;
	float		fov;
	int			y_shift;
	int			x_shift;
	t_point		origin;
}				t_plane;

typedef struct s_data
{
	float			max_x;
	float			max_y;
	float			max_z;
	float			min_z;
	unsigned int	obj_nb;
	t_point			centre;
	t_point			**arr;
	t_point_list	*list;
	t_point_list	*tail;
}				t_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_settings
{
	int		sel_x;
	int		sel_y;
	int		sel_z;
	float	mana;
}				t_settings;

typedef struct s_mlx
{
	int				win_x;
	int				win_y;
	t_data			data;
	t_plane			plane;
	t_obj_list		*live_objs;
	void			*mlx;
	void			*win;
	t_img			*img;
	float			*z_img;
	t_settings		setty;
	char			**argv;
}				t_mlx;

typedef struct s_pid_lst
{
	pthread_t			pid;
	unsigned int		layer;
	t_obj_list			*obj;
	t_mlx				*mlx;
	struct s_pid_lst	*next;
}				t_pid_lst;


typedef struct s_hsv
{
	float	p;
	float	q;
	float	t;
	float	r;
	float	g;
	float	b;
	float	hue;
	float	sat;
	float	lux;
	float	rgb_range;
	float	max_rgb;
	float	min_rgb;
	float	hue_progress;
	float	growing_rgb;
	float	dying_rgb;	
	float	f;
}	t_hsv;

//march_colors.c

unsigned int	hsv_to_rgb(float hue, float sat, float val);
unsigned int	rainbow_gradient(int iteration);
unsigned int	trippy_gradient(int iteration);
unsigned int	teal_palette(int iteration);

//main.c

void	my_pixel_put(t_mlx *mlx, int x, int y, float z, int color);

//easy_startup_functions.c

int		juice_the_pc(char flag, char **argv, t_mlx *mlx);

//input_handling.c

int		clean_exit(t_mlx *mlx);
int		handle_mouse(int keysym, int x, int y, t_mlx *mlx);
int		handle_keypress(int keysym, t_mlx *mlx);

//parsing.c

int		is_format(char *format, char *path);
int		line_parser(char *line);
int		file_parser(int fd);
int		data_parser(char *ls_out);

//parse_minions.c

int		is_leap(const char *s);
int		is_thirty(int month);
int		is_validay(int leap, int month, char *day);
int		is_date(char *line);
int		is_time(char *line);

//get_zed_data.c

int		get_zed_data(char **argv, int file, t_mlx *mlx);
int		zed_data_birth(t_point_list *data, t_mlx *mlx);

//get_fdf_data.c

int		get_fdf_data(char **argv, t_mlx *mlx);
int		fdf_data_birth(t_point **data, t_mlx *mlx);
t_point	**list_to_arr(t_point_list *list, size_t max_x, size_t max_y);

//checky_functions.c

void	ft_free_arr(char **arr);
void	ft_free_point_list(t_point_list *list);
void	ft_free_obj_list(t_obj_list *obj);
void	ft_free_pid_lst(t_pid_lst **list);

void	ft_print_point_arr(t_point **arr, int max_x);

//math_stuff.c

float	ft_anglef(t_point a, t_point o, t_point b);
float	ft_areaf(t_point a, t_point b, t_point c);
int	    is_inside(t_point p, t_point a, t_point b, t_point c);

//math_utils.c

int	    point_equal(t_point a, t_point b);
t_point	any_not_obtuse(t_point a, t_point b, t_point c);
float	ft_distf(t_point a, t_point b);
float	ft_absf(float f);
t_point	*to_zero(t_point *p);
t_point	*to_one(t_point *p);

t_point	major_z(t_point a, t_point b);
t_point	major_x(t_point a, t_point b);
t_point	major_y(t_point a, t_point b);
t_point	minor_z(t_point a, t_point b);
t_point	minor_x(t_point a, t_point b);
t_point	minor_y(t_point a, t_point b);

//math_sidekicks.c

int		ft_isuint(const char *s);
int		ft_isfloat(const char *s);
int		ft_isfloat_space(const char *s);
float	ft_atof(const char *nptr);

int		ft_atohexi(const char *nptr);

//shapemakers.c

int		fill_area(t_point a, t_point b, t_point c, int color, t_mlx *mlx);
int		fill_line(t_point a, t_point b, int color, t_mlx *mlx);
int		place_axis(float max_z, float max_x, float max_y, t_mlx *mlx);
int		point_to_rombus(t_point p, float value, int color, t_mlx *mlx);
int		point_to_cross(t_point p, float value, int color , t_mlx *mlx);

unsigned int blend_colors(unsigned int src, unsigned int dest, unsigned char alpha);

//mercatore_projection.c

int		merca_obj_list(t_obj_list *list, size_t radius, int max_x, int max_y);

//point_masters.c

void	put_point(t_point p, int color, t_mlx *mlx);
t_point	rotate_point(t_point p, t_point c, t_mlx *mlx);
t_point	get_centre(t_point *data, int pt_num);
t_point	get_list_centre(t_point_list *data, int pt_num);

t_point	zed_norm(t_point p);
t_point	fdf_norm(t_point p, t_mlx *mlx);

/* t_point_list    *z_quick_sort(float min_z, float max_z, t_point_list *list);
void				print_z_list(t_point_list *list); */

//pid_lst_utils.c

int			ft_pid_lst_append(t_pid_lst **list, t_pid_lst **tail, pthread_t pid);
void		ft_print_pid_lst(t_pid_lst *list);

//point_obj_list_utils.c

void	ft_free_obj_list(t_obj_list *obj);
int		ft_lstadd_point_tail(t_point_list **list, t_point_list **tail,
			int color, float value, t_point point);
int		ft_lstadd_obj_tail(t_obj_list *obj_tail, t_point_list **points,
			int color, int value, t_point point);
int		ft_lstnew_obj(t_obj_list **obj);

//base_plotting.c

void	put_obj(t_obj_list *obj, t_mlx *mlx);
void	put_data(t_mlx *mlx);

//thread_plotting.c

void	*put_layer_thread(void *arg);
void	put_data_thread(t_mlx *mlx);

#endif