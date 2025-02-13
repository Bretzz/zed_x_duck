/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   march_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:55:05 by mapascal          #+#    #+#             */
/*   Updated: 2025/02/13 14:38:33 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

unsigned int	hsv_to_rgb(float hue, float sat, float val);
unsigned int	rainbow_gradient(int iteration);
unsigned int	trippy_gradient(int iteration);
unsigned int	teal_palette(int iteration);

// Funzione per convertire HSV in RGB (ritorna un colore in formato 0xRRGGBB)
unsigned int	hsv_to_rgb(float hue, float sat, float val)
{
	t_hsv				hsv;
	int					i;
	float				vals[4];
	static const int	map[6][3] = {{0, 3, 1}, {2, 0, 1}, {1, 0, 3},
	{1, 2, 0}, {3, 1, 0}, {0, 1, 2}};
	float	band_width = 60.0f;

	hue = fmod(hue, 360.0);
	i = (int)(hue / band_width);
	hsv.hue_progress = (hue / band_width) - i;
	hsv.max_rgb = val;
	hsv.rgb_range = sat * hsv.max_rgb;
	hsv.min_rgb = hsv.max_rgb - hsv.rgb_range;
	hsv.dying_rgb = hsv.min_rgb + hsv.rgb_range * (1 - hsv.hue_progress);
	hsv.growing_rgb = hsv.min_rgb + hsv.rgb_range * hsv.hue_progress;
	vals[0] = hsv.max_rgb;
	vals[1] = hsv.min_rgb;
	vals[2] = hsv.dying_rgb;
	vals[3] = hsv.growing_rgb;
	return (((int)(vals[map[i][0]] * 255) << 16) |
			((int)(vals[map[i][1]] * 255) << 8) |
			(int)(vals[map[i][2]] * 255));
}

/*Colora con gradiente di colori dell'arcobaleno*/
unsigned int	rainbow_gradient(int iteration)
{
	float	t;
	int		r;
	int		g;
	int		b;

	t = iteration / 1881.0;
	r = (int)(sin(t * M_PI * 2) * 127 + 128);
	g = (int)(sin((t * M_PI * 2) + 2 * M_PI / 3) * 127 + 128);
	b = (int)(sin((t * M_PI * 2) + 4 * M_PI / 3) * 127 + 128);
	return ((r << 16) | (g << 8) | b);
}

/* Colora con colori verde e azzurro*/
unsigned int	teal_palette(int iteration)
{
	static const unsigned int	colors[] = {
		0x006400,
		0x228B22,
		0x32CD32,
		0x00FA9A,
		0x40E0D0,
		0x48D1CC,
		0x20B2AA
	};

	return (colors[iteration % 7]);
}

/* valore random negativo che pero funzia*/
unsigned int	trippy_gradient(int iteration)
{
	float	t;
	int		r;
	int		g;
	int		b;

	t = iteration / 1881.0;
	r = (int)(sin(t * -3.52 * 2) * 127 + 128);
	g = (int)(sin((t * -3.52 * 2) + 2 * -3.52 / 3) * 127 + 128);
	b = (int)(sin((t * -3.52 * 2) + 4 * -3.52 / 3) * 127 + 128);
	return ((r << 16) | (g << 8) | b);
}
