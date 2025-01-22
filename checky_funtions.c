/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checky_funtions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:26:33 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/22 14:29:58 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

void	ft_free_arr(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*removes the '\n' if present at the end of the last string
of the array*/
char	**back_trim_nl(char **arr)
{
	int	i;
	int	ii;

	ii = 0;
	while (arr[ii + 1] != 0)
		ii++;
	i = 0;
	while (arr[ii][i + 1] != '\0')
		i++;
	if (arr[ii][i] == '\n')
		arr[ii][i] = '\0';
	return (arr);
}

/*the functions returns the float value of the number
written on the string after the dot (.). Initially skips all the blank spaces
and numbers so you can use it also at the beginning of the cycle*/
static float	ft_get_decimals(const char *nptr)
{
	float	dec;
	size_t	len;

	while (ft_strchr(" \f\n\r\t\v", (char)*nptr) && *nptr)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		nptr++;
	if (*nptr++ != '.')
		return (0);
	len = 0;
	while (nptr[len + 1] >= '0' && nptr[len + 1] <= '9')
		len++;
	dec = 0;
	while (nptr[len] >= '0' && nptr[len] <= '9')
	{
		dec = dec / 10 + (nptr[len] - '0');
		printf("len=%zu: %f\n", len, dec);
		len--;
	}
	return (dec / 10);
}

/* somehow adds a 0.000001 at the end of the number */
float	ft_atof(const char *nptr)
{
	int				sign;
	float			nb;

	while (ft_strchr(" \f\n\r\t\v", (char)*nptr) && *nptr)
		nptr++;
	sign = 1;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	nb = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr == '.')
		nb += ft_get_decimals(nptr);
	return (nb * sign);
}
