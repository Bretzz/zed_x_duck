/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nest_putuns_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:46:38 by topiana-          #+#    #+#             */
/*   Updated: 2024/12/14 14:38:11 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nest_putuns_fd(int fd, unsigned int nb)
{
	int		count;
	char	digit;

	count = 0;
	if (nb >= 10)
		count += nest_putuns_fd(fd, (nb / 10));
	digit = (nb % 10) + '0';
	count += west_putchar_fd(fd, digit);
	return (count);
}

/* int	main(int argc, char *argv[])
{
	printf("=%i\n", nest_putuns_fd(UINT32_MAX, 1));
	write(1, "\n", 1);
	printf("=%i", printf("%u", UINT32_MAX));
	return (0);
} */
