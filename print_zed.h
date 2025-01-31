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

# ifndef ESC_KEY
#  define ESC_KEY 65307
# endif

# ifndef MAX_WIN_X
#  define MAX_WIN_X 1920
# endif

# ifndef MAX_WIN_Y
#  define MAX_WIN_Y 1080
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

# include <stdio.h>

typedef struct s_point
{
	float	z;
	float	x;
	float	y;
}				t_point;

typedef struct s_point_list
{
	t_point 			point;
	unsigned int		color;
	struct s_point_list *z_sorted_next;
	struct s_point_list	*next;
}				t_point_list;


typedef struct s_pixel
{
	int		z;
	int		x;
	int		y;
}				t_pixel;

typedef struct s_plane
{
	float		r_z;
	float		r_x;
	float		r_y;
	float		fov;
	t_point		origin; //origin's coordinate are pixel-based and z = 0;
}				t_plane;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mlx
{
	int			win_x;
	int			win_y;
	void		*mlx;
	void		*win;
	t_point		*data;
	t_point_list *live_points;
	t_plane		plane;
	t_img		*img;
	float		*z_img;
}				t_mlx;


//main.c

void		my_pixel_put(t_mlx *mlx, int x, int y, float z, int color);

//easy_startup_functions.c

int			juice_the_pc(t_mlx *mlx);

//input_handling.c

int			clean_exit(t_mlx *mlx);
int			handle_mouse(int keysym, int x, int y, t_mlx *mlx);
int			handle_keypress(int keysym, t_mlx *mlx);

int			ft_isuint(const char *s);
int			ft_isfloat(const char *s);
int			ft_isfloat_space(const char *s);

//checky_functions.c

float		ft_atof(const char *nptr);
void		ft_free_arr(char **arr);
char		**back_trim_nl(char **arr);
int			ft_lstadd_point_tail(t_point_list **list, t_point_list **tail, int color, t_point point);

//parsing.c

int		is_time(char *line);
int		is_date(char *line);
int		line_parser(char *line);
int		is_format(char *format, char *path);
int		file_parser(int fd);
int		data_parser(char *ls_out);

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
t_point	major_z(t_point a, t_point b);
t_point	major_x(t_point a, t_point b);
t_point	major_y(t_point a, t_point b);
t_point	minor_z(t_point a, t_point b);
t_point	minor_x(t_point a, t_point b);
t_point	minor_y(t_point a, t_point b);

/* t_point_list    *z_quick_sort(float min_z, float max_z, t_point_list *list);
void			print_z_list(t_point_list *list); */

#endif