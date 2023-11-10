/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:49:47 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/11/03 11:07:52 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_token	*create_token_list(char *token, e_token_types type)
{
	t_token	*new;	

	new = (t_token *)malloc(sizeof(t_token));
	new->value = token;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	insert_at_end(t_token **head, char *str, e_token_types type)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = create_token_list(str, type);
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}
}

// void	free_list(t_token *lst)
// {
// 	t_token	*next;

// 	while (lst)
// 	{
// 		next = lst->next;
// 		// free(lst->value);
// 		free(lst);
// 		lst = next;
// 	}
// }

void	ft_token_lst_clear(t_token **lst)
{
	t_token	*curr;
	t_token	*next;

	if (!(*lst))
		return ;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*lst = NULL;
}