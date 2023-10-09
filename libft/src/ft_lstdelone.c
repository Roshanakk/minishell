/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:50:18 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/09 13:33:47 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !(*del))
		return ;
	tmp = lst;
	lst = lst->next;
	(*del)(tmp->content);
	free(tmp);
}
