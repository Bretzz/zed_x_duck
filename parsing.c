/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsinng.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:15:55 by totommi           #+#    #+#             */
/*   Updated: 2025/01/22 02:24:47 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	is_time(char *line);
int	is_date(char *line);
int	line_parser(char *line);
int file_parser(int fd);


/* takes a char pointer as a parameter
RETURNS: 1 if the string begins with a 'date', 0 if it doesn't 
date: yyyy/mm/dd */
int	is_date(char *line)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (*line == '\0')
			return (0);
		if ((i == 4 || i == 7))
		{
			if (*line != '/')
			{
				ft_printf("date: backslash [%i] strike OUT\n", i);
				return (0);
			}
		}
		else if (!ft_isdigit(*line))
		{
			ft_printf("date: digit [%i] strike OUT\n", i);
			return (0);
		}
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

	i = 0;
	while (i < 8)
	{
		if (*line == '\0')
			return (0);
		if ((i == 2 || i == 5))
		{
			if (*line != ':')
			{
				ft_printf("time: colon [%i] strike OUT\n", i);
				return (0);
			}
		}
		else if (!ft_isdigit(*line))
		{
			ft_printf("time: digit [%i] strike OUT\n", i);
			return (0);
		}
		line++;
		i++;
	}
	return (1);
}

/* 2020/12/04 00:00:00      1607040000       6000.   4000.   -800.       5580.    430.    1.790    0.052
take a char pointer as a parameter
RETURNS: 1 if the line is formatted as the line above, 0 if it isn't */
int	line_parser(char *line)
{
	int	i;

	if (!line)
		return (0);
	if (ft_wdcount(line, ' ') != 10)
		return (0);
	if (!is_date(line))
		return (0);
	line += 10;
	if (*line != ' ')
		return (0);
	line++;
	if (!is_time(line))
		return (0);
	line += 8;
	i = 0;
//	ft_printf("date + time OK\n");
	while (i < 8)
	{
		if (*line == '\0' || *line != ' ')
			return (0);
//		ft_printf("element close correctly\n");
		while (*line && *line == ' ')
			line++;
		if (i > 0 && i <= 5 && i != 3)
		{
			while (*line && ft_isdigit(*line))
				line++;
			if (!*line || *line != '.')
				return (0);
			line++;
//			ft_printf("'digit.' element OK\n");
		}
		else if (i == 3)
		{
			if (!*line || *line != '-')
				return (0);
			line++;
			while (*line && ft_isdigit(*line))
				line++;
			if (!*line || *line != '.')
				return (0);
			line++;
//			ft_printf("'-digit.' element OK\n");
		}
		else if (i >= 6)
		{
			if (!ft_isfloat_space(line))
				return (0);
			while (*line && (ft_isdigit(*line) || *line == '.'))
				line++;
//			ft_printf("'float' element OK\n");
		}
		else
		{
			while (*line && ft_isdigit(*line))
				line++;
//			ft_printf("'digit' element OK\n");
		}
		i++;
		//if (i < 6 || (i > 16 && i < 23) || (i > 28 && i < 31) || (i > 36 && i < 39) || (i > 44 & i < 51) || ())
	}
	if (*line != '\n')
		return (0);
	return (1);
}

/* #DATE      HOUR          EPOCH               X       Y       Z         Vp     dVp     VpVs    dVpVs 
takes a file descriptor as parameter 
Reads the file line by line until it matches the line above
RETURNS: 0 if all the lines after respect the syntax,
otherwhise returns the line (number) that dropped the error*/
int	file_parser(int fd)
{
	int		i;
	int		header;
	char	*line;
	
	header = 0;
	i = 1;
	while ((line = get_next_line(fd)))
	{
		if (!ft_strncmp("#DATE      HOUR          EPOCH               X       Y       Z         Vp     dVp     VpVs    dVpVs ", line, 100))
		{
			header = 1;
			free(line);
			i++;
			break ;
		}
		free(line);
		i++;
	}
	if (!header)
		return (i);
	while ((line = get_next_line(fd)))
	{
		if (!line_parser(line))
		{
			free(line);
			return (i);
		}
		free(line);
		i++;
	}
	return (0);
}
