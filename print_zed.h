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

# define MY_PI 3.14159265359

# include "mlx.h"
# include "libft.h"
# include "duck_engine.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <float.h>

# include <stdio.h>
# include <time.h> 


typedef struct s_values
{
	float	measrd;
	float	error;
}				t_values;

typedef struct s_data_list
{
	t_point				point;
	void				*values;
	struct s_data_list *next;
}				t_data_list;

//stats of the input data (aka world space point)
//we're jsut using centre and obj_nb
typedef struct s_data
{
	float			limx[2];	//xmax [0] and xmin [1]
	float			limy[2];	//ymax [0] and ymin [1]
	float			limz[2];	//zmax [0] and zmin [1]
	float			val_lim[2];	//analized value max [0] and min [1]
	float			err_lim[2]; //analized value's error max [0] and min [1]
	t_point			centre;
	t_point			**arr;		//useful way to store grid data
	t_data_list		*list;		//just unrelated data storing
	t_data_list		*tail;
}				t_data;

//mlx img variables
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

//user settings
typedef struct s_settings
{
	int				sel_x;	//user selected x-layer
	int				sel_y;	//user selected y-layer
	int				sel_z;	//user selected z-layer
	unsigned char	right_click;		
	float			mana;
}				t_settings;

//mlx big struct
typedef struct s_mlx
{
	int				win_x;
	int				win_y;
	int				xmouse_s;
	int				ymouse_s;
	t_data			data;
	t_duck			duck;
	void			*mlx;
	void			*win;
	t_img			*img;
	float			*z_img;
	t_settings		setty;
	char			**argv;
}				t_mlx;

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

//my_shapemakers.c

int		my_point_to_rombus(t_point p, void *data, int color, t_duck *duck);
int		my_point_to_cross(t_point p, void *data, int color , t_duck *duck);
int		my_point_to_sphere(t_point p, void *data, int color, t_duck *duck);

//easy_startup_functions.c

int		juice_the_pc(char **argv, t_mlx *mlx);

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
//int		zed_data_birth(t_data_list *data, int file_num, t_mlx *mlx);
t_point	zed_norm(t_point p);

//data_list.c

int		ft_datalst_add_tail(t_data_list **list, t_data_list **tail,
			void *values, t_point point);
t_point	get_data_list_centre(t_data_list *list, int pt_num);
void	ft_free_data_list(t_data_list *list, void (*del)(void *));

//checky_functions.c

void	ft_print_point_arr(t_point **arr, int max_x);

#endif