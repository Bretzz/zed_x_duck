/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_shapemakers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 05:07:52 by totommi           #+#    #+#             */
/*   Updated: 2025/02/18 15:27:55 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	my_point_to_rombus(t_point p, void *data, int color, t_duck *duck);
int	my_point_to_cross(t_point p, void *data, int color , t_duck *duck);
int	my_point_to_sphere(t_point p, void *data, int color, t_duck *duck);

int	my_point_to_rombus(t_point p, void *data, int color, t_duck *duck)
{
	float 	value;
	int		points;
	t_point vertex[6];

	//obj creation and value assignment
	if (!duck_objnew(&duck->live_objs))
		return (-1);
	duck->live_objs->obj_tail->data = data;
	duck->live_objs->obj_tail->origin = p;
	duck->live_objs->obj_tail->tag = DATA;
	points = 0;
	while (points < 6)
	{
		vertex[points] = p;
		points++;
	}
	value = *(float *)data;
	//value = 1;
	vertex[0].z += value;
	vertex[1].z -= value;
	vertex[2].x += value;
	vertex[3].x -= value;
	vertex[4].y += value;
	vertex[5].y -= value;
	//rombus
	points = 0;
	points += fill_area(vertex[5], vertex[2], vertex[0], color, duck);
	points += fill_area(vertex[5], vertex[2], vertex[1], color, duck);
	points += fill_area(vertex[5], vertex[3], vertex[0], color, duck);
	points += fill_area(vertex[5], vertex[3], vertex[1], color, duck);
	points += fill_area(vertex[4], vertex[2], vertex[0], color, duck);
	points += fill_area(vertex[4], vertex[2], vertex[1], color, duck);
	points += fill_area(vertex[4], vertex[3], vertex[0], color, duck);
	points += fill_area(vertex[4], vertex[3], vertex[1], color, duck);
	return (points);
}

int	my_point_to_cross(t_point p, void *data, int color , t_duck *duck)
{
	float	value;
	int		points;
	t_point vertex[6];

	//obj creation and value assignment
	if (!duck_objnew(&duck->live_objs))
		return (-1);
	duck->live_objs->obj_tail->data = data;
	duck->live_objs->obj_tail->origin = p;
	duck->live_objs->obj_tail->tag = DATA;
	points = 0;
	while (points < 6)
	{
		vertex[points] = p;
		points++;
	}
	value = *(float *)data;
	vertex[0].z += value;
	vertex[1].z -= value;
	vertex[2].x += value;
	vertex[3].x -= value;
	vertex[4].y += value;
	vertex[5].y -= value;
	points = 0;
	//cross
	points += fill_line(vertex[0], vertex[1], color, duck);
	points += fill_line(vertex[2], vertex[3], color, duck);
	points += fill_line(vertex[4], vertex[5], color, duck);
	return (points);
}

int	my_point_to_plato(t_point p, void *data, int color , t_duck *duck)
{
	float	value;
	int		points;
	float	ff_deg;
	t_point vertex[18];

	ff_deg = sqrt(2) / 2;
	//obj creation and value assignment
	if (!duck_objnew(&duck->live_objs))
		return (-1);
	duck->live_objs->obj_tail->data = data;
	duck->live_objs->obj_tail->origin = p;
	duck->live_objs->obj_tail->tag = DATA;
	points = 0;
	while (points < 18)
	{
		vertex[points] = p;
		points++;
	}
	value = *(float *)data;
	//1-pt apex
	vertex[0].y -= value;
	
	//4-pt top layer
	vertex[1].y -= value * ff_deg * ff_deg;
	vertex[1].x += (value * ff_deg)/* * ff_deg */;
	vertex[1].z += (value * ff_deg)/* * ff_deg */;
	vertex[2].y -= value * ff_deg * ff_deg;
	vertex[2].x += (value * ff_deg)/* * ff_deg */;
	vertex[2].z -= (value * ff_deg)/* * ff_deg */;
	vertex[3].y -= value * ff_deg * ff_deg;
	vertex[3].x -= (value * ff_deg)/* * ff_deg */;
	vertex[3].z -= (value * ff_deg)/* * ff_deg */;
	vertex[4].y -= value * ff_deg * ff_deg;
	vertex[4].x -= (value * ff_deg)/* * ff_deg */;
	vertex[4].z += (value * ff_deg)/* * ff_deg */;
	//8-pt middle layer
	vertex[5].z += value;
	vertex[6].z += value * ff_deg;
	vertex[6].x += value * ff_deg;
	vertex[7].x += value;
	vertex[8].x += value * ff_deg;
	vertex[8].z -= value * ff_deg;
	vertex[9].z -= value;
	vertex[10].x -= value * ff_deg;
	vertex[10].z -= value * ff_deg;
	vertex[11].x -= value;
	vertex[12].x -= value * ff_deg;
	vertex[12].z += value * ff_deg;
	//4-pt bottom layer
	vertex[13].y += value * ff_deg * ff_deg;
	vertex[13].x += (value * ff_deg)/* * ff_deg */;
	vertex[13].z += (value * ff_deg)/* * ff_deg */;
	vertex[14].y += value * ff_deg * ff_deg;
	vertex[14].x += (value * ff_deg)/* * ff_deg */;
	vertex[14].z -= (value * ff_deg)/* * ff_deg */;
	vertex[15].y += value * ff_deg * ff_deg;
	vertex[15].x -= (value * ff_deg)/* * ff_deg */;
	vertex[15].z -= (value * ff_deg)/* * ff_deg */;
	vertex[16].y += value * ff_deg * ff_deg;
	vertex[16].x -= (value * ff_deg)/* * ff_deg */;
	vertex[16].z += (value * ff_deg)/* * ff_deg */;
	//13-pt foot
	vertex[17].y += value;

	points = 0;
	//hat
	points += fill_area(vertex[0], vertex[1], vertex[2], color, duck);
	color += 3000;
	points += fill_area(vertex[0], vertex[2], vertex[3], color, duck);
	color += 3000;
	points += fill_area(vertex[0], vertex[3], vertex[4], color, duck);
	color += 3000;
	points += fill_area(vertex[0], vertex[4], vertex[1], color, duck);
	color += 3000;
	//belt
	points += fill_area(vertex[5], vertex[7], vertex[1], color, duck);
	color += 3000;
	points += fill_area(vertex[5], vertex[7], vertex[13], color, duck);
	color += 3000;
	points += fill_area(vertex[1], vertex[2], vertex[7], color, duck);
	color += 3000;
	points += fill_area(vertex[13], vertex[14], vertex[7], color, duck);
	color += 3000;
	//shoes
	points += fill_area(vertex[17], vertex[13], vertex[14], color, duck);
	color += 3000;
	points += fill_area(vertex[17], vertex[14], vertex[15], color, duck);
	color += 3000;
	points += fill_area(vertex[17], vertex[15], vertex[16], color, duck);
	color += 3000;
	points += fill_area(vertex[17], vertex[16], vertex[13], color, duck);
	color += 3000;
	return (points);
}

/* finds the points to draw an XZ circle of origin 'o' and radius 'r' */
int	fill_circle(t_point o, float r, int color, t_duck *duck)
{
	int		ret;
	float	x;
	t_point	p;
	float	incr;

	p = o;
	incr = 1 / (r);
	ret = 0;
	x = 0;
	while (x <= 2 * MY_PI)
	{
		p.x = o.x + (r * cosf(x));
		p.z = o.z + (r * sinf(x));
		//printf("x=%f, px=%f, py=%f, pz=%f\n", x, p.x, p.y, p.z);
		if (!(duck_point_to_obj_tail(duck->live_objs->obj_tail, color, 0x0, p)))
			return (-1);
		ret++;
		x += incr;
	}
	return (ret);
}

int	my_point_to_sphere(t_point o, void *data, int color, t_duck *duck)
{
	int		points;
	float	value;
	float	x;
	float	incr;
	t_point	p;

	(void)incr; (void)x;
	//obj creation and value assignment
	if (!duck_objnew(&duck->live_objs))
		return (-1);
	duck->live_objs->obj_tail->data = data;
	duck->live_objs->obj_tail->origin = o;
	duck->live_objs->obj_tail->tag = DATA;
	value = *(float *)data;
	incr = MY_PI / (2 * value);
	p = o;
	points = 0;
	x = 0.0f;
	while (x <= MY_PI)
	{
		p.y = o.y - (value * cosf(x));
		//printf("p.y=%f, x=%f, r=%f\n", p.y, x, value * sinf(x));
		points += fill_circle(p, value * sinf(x), color, duck);
		x += incr;
	}
	//points += fill_circle(p, value, color, duck);
	return (points);
}
