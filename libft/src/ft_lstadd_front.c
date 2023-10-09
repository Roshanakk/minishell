/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:33:32 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/01/30 17:35:05 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int main()
// {
// 	t_list	*a;
// 	t_list	*b;

// 	a = ft_lstnew("un");
// 	ft_lstadd_back(&a, "deux");
// 	ft_lstadd_back(&a, "trois");
	
// 	b = ft_lstnew("do");
// 	ft_lstadd_back(&b, "re");
// 	ft_lstadd_back(&b, "mi");
	
// 	while (a)
// 	{
// 		printf("%s ", a->content);
// 		a = a->next;
// 	}
// 	return (0);
// }