/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_sidekicks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:41:35 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/01 16:52:38 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	ft_isuint(const char *s);
int	ft_isfloat(const char *s);

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
