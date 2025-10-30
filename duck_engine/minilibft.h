/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:51:09 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/14 16:11:22 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBFT_H
# define MINILIBFT_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

//minilibft.h

int			ft_isdigit(int c);
int			ft_isspace(int c);
int			ft_atoi(const char *nptr);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);

#endif
