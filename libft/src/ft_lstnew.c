/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:12:38 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/09 11:19:44 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, int index)
{
	t_list	*cell;

	cell = malloc(sizeof(t_list));
	if (!cell)
		return (NULL);
	cell->content = content;
	cell->index = index;
	cell->next = NULL;
	return (cell);
}
