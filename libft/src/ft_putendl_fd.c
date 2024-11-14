/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:14:19 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/08 12:00:37 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_putendl_fd(char *s, int fd)
// {
// 	char	*tmp;

// 	tmp = ft_strjoin(s, "\n");
// 	ft_putstr_fd(tmp, fd);
// 	free(tmp);
// }

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\n", fd);
}
