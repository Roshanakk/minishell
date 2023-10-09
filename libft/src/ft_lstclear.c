/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:30:59 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/09 13:38:54 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*curr;
	t_list	*next;

	if (!(*lst))
		return ;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		// free(curr->content);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
