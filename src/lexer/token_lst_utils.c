/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:47:49 by balacam           #+#    #+#             */
/*   Updated: 2023/12/09 16:57:24 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to create a new token
t_token	*create_token_list(char *value, char *backup, int type, int status)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token) * 1);
	if (!(new_node))
		return (NULL);
	new_node->value = value;
	new_node->value_backup = backup;
	new_node->type = type;
	new_node->status = status;
	new_node->next = NULL;
	return (new_node);
}

// Function to insert a new token at the end of the list
void	insert_at_end(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (*head == NULL)
	{
		*head = new_token;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_token;
	}
}

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
		free(curr->value);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
