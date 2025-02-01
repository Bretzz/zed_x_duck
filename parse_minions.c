/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_minions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:09:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/01 18:09:55 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	is_leap(const char *s);
int	is_thirty(int month);
int	is_validay(int leap, int month, char *day);
int	is_date(char *line);
int	is_time(char *line);

/* takes a string as a parameter.
converts it into int using ft_atoi() and checks weather
the yesr is a leap year.
NOTE: the year is expected to be exactly at the beginning of the string:
ex: "1493-01-27", not "   1492-...".
RETURNS: 1 if it's a leap year, 0 if it isn't. */
int	is_leap(const char *s)
{
	int	year;

	if (!s)
		return (0);
	if (!ft_isdigit(*s))
		return (0);
	year = ft_atoi(s);
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return (1);
	return (0);
}

/* takes an int as parameter.
checks weather is a month with 30 days or not. */
int	is_thirty(int month)
{
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return (1);
	return (0);
}

/* takes two ints and a string as parameters.
checks wether the day written in the string (numeric format: '12')
is a valid day for the year (leap true/false) and the month (second int).
RETURNS: 1 if it's a valid day, 0 if it isn't. */
int	is_validay(int leap, int month, char *day)
{
	if (is_thirty(month) && ft_strncmp("30", day, 2) < 0)
		return (0);
	if (month == 2
		&& ((leap && ft_strncmp("29", day, 2) < 0)
			|| (!leap && ft_strncmp("28", day, 2) < 0)))
		return (0);
	if (!is_thirty(month) && month != 2 && ft_strncmp("31", day, 2) < 0)
		return (0);
	return (1);
}

/* takes a char pointer as a parameter
RETURNS: 1 if the string begins with a 'date', 0 if it doesn't 
date: yyyy/mm/dd */
int	is_date(char *line)
{
	int	i;
	int	leap;

	leap = is_leap(line);
	i = 0;
	while (i < 10)
	{
		if (*line == '\0')
			return (0);
		if ((i == 4 || i == 7) && *line != '/')
			return (0);
		else if (i == 0 && (!(ft_isdigit(*line)) || *line == '0'))
			return (0);
		else if (i == 5 && (!(ft_isdigit(*line)) || !(ft_isdigit(*(line + 1)))
				|| ft_strncmp("12", line, 2) < 0))
			return (0);
		else if (i == 8 && (!is_validay(leap, ft_atoi(line - 3), line)))
			return (0);
		line++;
		i++;
	}
	return (1);
}

/* takes a char pointer as a parameter
RETURNS: 1 if the string begins with a 'timestamp', 0 if it doesn't
timestamp: hh:mm:ss */
int	is_time(char *line)
{
	int	i;

	if (line == NULL)
		return (0);
	i = 0;
	while (i < 8)
	{
		if (line[i] == '\0')
			return (0);
		if (i == 0 && (!ft_isdigit(line[i]) || line[i] > '2'))
			return (0);
		else if (i == 1 && (!ft_isdigit(line[i])
				|| (line[0] == '2' && line[i] > '4')))
			return (0);
		else if ((i == 2 || i == 5) && line[i] != ':')
			return (0);
		else if ((i == 3 || i == 6) && (!ft_isdigit(line[i])
				|| line[i] > '5'))
			return (0);
		else if ((i == 4 || i == 7) && !ft_isdigit(line[i]))
			return (0);
		i++;
	}
	return (1);
}
