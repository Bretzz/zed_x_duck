/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   west_putstr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:25:27 by topiana-          #+#    #+#             */
/*   Updated: 2024/12/14 14:38:20 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	west_putstr_fd(int fd, char *s)
{
	int	i;

	if (!s)
		return (west_putstr_fd(fd, "(null)"));
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

/* int	main(int argc, char *argv[])
{
	if (argc == 3)
		printf("|=%i", west_putstr_fd(1, argv[1], *argv[2]));
	else
		printf("|=%i", west_putstr_fd(1, argv[1]));
	return (0);
} */
