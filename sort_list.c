/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:54:34 by totommi           #+#    #+#             */
/*   Updated: 2025/01/29 04:21:46 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

t_point_list    *z_quick_sort(float min_z, float max_z, t_point_list *list);
void	print_z_list(t_point_list *list);

/* ! ! !DA RIMUOVRERE ! ! ! */
void	print_z_list(t_point_list *list)
{
	while (list != NULL)
	{
		printf("%f\n", list->point.z);
		list = list->z_sorted_next;
	}
}


/* takes a t_point_list pointer and
the minimum/maximum values of z as a parameters.
finds the point with higher z-value and sets his z_sorted next
value to point to the second higher z-value point and so on.
RETURNS: the point with lower z-value. */
t_point_list    *z_quick_sort(float min_z, float max_z, t_point_list *list)
{
	float			min_max_pivot[5]; //0 = min_higher, 1 = max_higher, 2 ..., 3..., 4 = curr_pivot
	t_point_list	*lower_tail = NULL;
	t_point_list	*higher_tail = NULL;
	t_point_list	*lower = NULL;
	t_point_list	*higher = NULL;
	t_point_list	*runner;

	if (list->next == NULL)
		return (list);
	min_max_pivot[4] = (min_z + max_z) / 2;
	runner = list;
	while (runner != NULL)
	{
		if (!higher && runner->point.z > min_max_pivot[4])
		{
			min_max_pivot[0] = runner->point.z;
			min_max_pivot[1] = runner->point.z;
			higher = runner;
			higher_tail = runner;
		}
		else if (higher && runner->point.z > min_max_pivot[4])
		{
			if (runner->point.z < min_max_pivot[0])
				min_max_pivot[0] = runner->point.z;
			else if (runner->point.z > min_max_pivot[1])
				min_max_pivot[1] = runner->point.z;
			higher_tail->z_sorted_next = runner;
			higher_tail = runner;
		}
		else if (!lower && runner->point.z < min_max_pivot[4])
		{
			min_max_pivot[2] = runner->point.z;
			min_max_pivot[3] = runner->point.z;
			lower = runner;
			lower_tail = runner;
		}
		else if (lower && runner->point.z < min_max_pivot[4])
		{
			if (runner->point.z < min_max_pivot[2])
				min_max_pivot[2] = runner->point.z;
			else if (runner->point.z > min_max_pivot[3])
				min_max_pivot[3] = runner->point.z;
			lower_tail->z_sorted_next = runner;
			lower_tail = runner;
		}
		runner = runner->z_sorted_next;
	}
	print_z_list(higher);
	printf("\n========\nPIVOT: %f\n========\n", min_max_pivot[4]);
	print_z_list(lower);
	printf("! ! ! BREAK ! ! !\n");
	if (lower != NULL)
	{
		lower = z_quick_sort(min_max_pivot[2], min_max_pivot[3], lower);
		higher = z_quick_sort(min_max_pivot[0], min_max_pivot[1], lower);
	}
	return (higher);
}