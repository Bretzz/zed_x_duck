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

# define UNUSED(x) (void)(x)

# include "mlx.h"
# include <math.h>
# include "libft.h"

# include <stdio.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_mlx
{
	int		win_x;
	int		win_y;
	void	*mlx;
	void	*win;
	t_img	*img;
}				t_mlx;

//main.c
void		my_pixel_put(t_img *data, int x, int y, int color);

//easy_startup_functions.c
int			juice_the_pc(t_mlx *mlx);

//input_handling.c
int			clean_exit(t_mlx *mlx);
int			handle_mouse(int keysym, int x, int y, t_mlx *mlx);
int			handle_keypress(int keysym, t_mlx *mlx);

int			ft_isfloat(const char *s);
int			ft_isuint(const char *s);

//checky_functions.c
float		ft_atof(const char *nptr);
void		ft_free_arr(char **arr);
char		**back_trim_nl(char **arr);

#endif