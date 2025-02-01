/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:15:55 by totommi           #+#    #+#             */
/*   Updated: 2025/02/01 18:09:50 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_zed.h"

int	is_format(char *format, char *path);
int	line_parser(char *line);
int	file_parser(int fd);
int	data_parser(char *ls_out);

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
	if (*(line++) != ' ')
		return (0);
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

/* takes a 'format' string and a 'path' string as parameters.
checks if the file at the endd of the path is of the format specified.
RETURNS: 1 if it is, 0 if it isn't. */
int	is_format(char *format, char *path)
{
	int	i;

	i = 0;
	if (!format || !path)
		return (0);
	while (path[i] != '\0')
		i++;
	while (i >= 0 && path[i] != '/')
		i--;
	while (path[i] != '\0' && path[i] != '.')
		i++;
	if (ft_strncmp(format, &path[i], ft_strlen(format) + 1))
		return (0);
	return (1);
}

/* takes the path of the folder as parameter.
RETURNS: 1 if all the file contained respect the format, 0 if not. 
REMEMBER TO CHECKARE IL FORMATEO DEL FILE (.*) */
int	data_parser(char *ls_out)
{
	int		i;
	int 	fd;
	int		line;
	char	*itoa;
	char	**paths;
	
	paths = ft_split(ls_out, ' ');
	if (!paths)
		return (0);
	i = 0;
	while (paths[i] != NULL)
	{
		ft_printf("parsing: %s ...\n", paths[i]);
		fd = open(paths[i], O_RDONLY);
		if ((line = file_parser(fd)))
		{
			(void)!write(2, &paths[i][5], ft_strlen(&paths[i][5]));
			(void)!write(2, ": line [", 8);
			itoa = ft_itoa(line);
			(void)!write(2, itoa, ft_strlen(itoa));
			(void)!write(2, "]: file parse error\n", 21);
			free(itoa);
			ft_free_arr(paths);
			return (0);
		}
		close(fd);
		i++;
	}
	ft_free_arr(paths);
	return (1);
}
