/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_sidekicks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:41:35 by topiana-          #+#    #+#             */
/*   Updated: 2025/01/15 13:44:37 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	ft_isuint(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (!ft_isdigit(s[i])
			&& s[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int	ft_isfloat(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '.' && !ft_isdigit(s[i])
			&& !(s[i] == '-' || s[i] == '+'))
			return (0);
		i++;
	}
	return (1);
}

/* exactly as ft_isfloat but read the string up to a whitespace (ft_isspace) */
int	ft_isfloat_space(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0' && !ft_isspace(s[i]))
	{
		if (s[i] != '.' && !ft_isdigit(s[i])
			&& !(s[i] == '-' || s[i] == '+'))
			return (0);
		i++;
	}
	return (1);
}
