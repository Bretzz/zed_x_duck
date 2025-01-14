/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   west_putnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:26:58 by topiana-          #+#    #+#             */
/*   Updated: 2024/12/14 14:38:17 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	west_putnbr_fd(int fd, int nb)
{
	int		count;
	char	digit;

	count = 0;
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		write(fd, "-", 1);
		count++;
		nb *= -1;
	}
	if (nb >= 10)
		count += west_putnbr_fd(fd, nb / 10);
	digit = (nb % 10) + '0';
	count += west_putchar_fd(fd, digit);
	return (count);
}

/* #include <stdio.h>

int	main(int argc, char *argv[])
{
	printf("|=%i\n", west_putnbr_fd(ft_atoi(argv[1]), ft_atoi(argv[2])));
	printf("|=%i\n", printf("%i", ft_atoi(argv[1])));
	return (0);
} */
