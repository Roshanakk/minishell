/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testshell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:27:59 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/04 11:51:55 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSHELL_H
# define TESTSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <aio.h>
#include <fcntl.h>
#include <unistd.h>

int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnjoin(char const *s1, char const *s2, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	**ft_free_double_char(char	**str, size_t	l);
size_t	ft_cmpt(char const *s, char c);

#endif

