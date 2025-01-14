/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:09:47 by topiana-          #+#    #+#             */
/*   Updated: 2024/11/22 16:31:07 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*sdup;
	size_t			size;

	size = ft_strlen(s) + 1;
	sdup = (char *)ft_calloc(size, sizeof(char));
	if (sdup == NULL)
		return (NULL);
	ft_strlcpy(sdup, s, size);
	return (sdup);
}
/*
#include <string.h>
#include <stdio.h>
int	main(int argc, char *argv[])
{
	//printf("%s\n", strdup(argv[1]));
	printf("%s\n", ft_strdup(argv[1]));
	return (0);
}*/
