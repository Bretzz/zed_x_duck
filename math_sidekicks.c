/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_sidekicks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:41:35 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/21 12:36:54 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

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

int	ft_isfloat(const char *s)
{
	int	i;
	int point;

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
	int point;

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
