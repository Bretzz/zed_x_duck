/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_sidekicks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:41:35 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/12 17:05:39 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int		ft_isuint(const char *s);
int		ft_isfloat(const char *s);
int		ft_isfloat_space(const char *s);
float	ft_atof(const char *nptr);

int		ft_atohexi(const char *nptr);

/* checks weather the value written in the string
can be converted in uint, pattern="[+][0-9]", with no whitespaces.
RETURNS: 1 if respects the pattern, 0 if it doesn't. */
int	ft_isuint(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '+')
		i++;
	while (s[i] != '\0')
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

/* checks weather the value written in the string
can be converted in float, pattern="[+-][0-9].[0-9]", with no whitespaces.
RETURNS: 1 if respects the pattern, 0 if it doesn't. */
int	ft_isfloat(const char *s)
{
	int	i;
	int	point;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	point = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '.' && point == 0)
			point = 1;
		else if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

/* exactly as ft_isfloat but read the string up to a whitespace (ft_isspace) */
int	ft_isfloat_space(const char *s)
{
	int	i;
	int	point;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	point = 0;
	while (s[i] != '\0' && !ft_isspace(s[i]))
	{
		if (s[i] == '.' && point == 0)
			point = 1;
		else if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

/*the functions returns the float value of the number
written on the string after the dot (.). Initially skips all the blank spaces
and numbers so you can use it also at the beginning of the cycle*/
/* ! ! ! INVALI READS ON NUMBERS THAT END WITH A '.' ! ! ! */
float	ft_get_decimals(const char *nptr)
{
	float	dec;
	size_t	len;

	if (nptr == NULL)
		return (0);
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
//		printf("len=%zu: %f\n", len, dec);
		len--;
	}
	return (dec / 10);
}

/* somehow adds a 0.000001 at the end of the number */
float	ft_atof(const char *nptr)
{
	int				sign;
	float			nb;

	if (nptr == NULL)
		return (0);
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

int		ft_atohexi(const char *nptr)
{
	int	nb;

	if (nptr == NULL)
		return (0);
	while (ft_strchr(" \f\n\r\t\v", (char)*nptr) && *nptr)
		nptr++;
	if (ft_strncmp("0x", nptr, 2) != 0)
		return (ft_atoi(nptr));
	nptr++;
	nb = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 16 + (*nptr - '0');
		nptr++;
	}
	return (nb);
}
