/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:02:34 by balacam           #+#    #+#             */
/*   Updated: 2023/12/09 16:57:42 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_type(t_token *token)
{
	if (token->type == WORD)
		printf("%s ", "WORD");
	else if (token->type == PIPE)
		printf("%s ", "PIPE");
	else if (token->type == REDIR_OUT)
		printf("%s ", "REDIR_OUT");
	else if (token->type == REDIR_IN)
		printf("%s ", "REDIR_IN");
	else if (token->type == HEREDOC)
		printf("%s ", "HEREDOC");
	else if (token->type == APPEND)
		printf("%s ", "APPEND");
	else if (token->type == VAR)
		printf("%s ", "VAR");
}

void	print_value(t_token *current)
{
	if (current->type == WORD
		|| current->type == VAR || current->type == HEREDOC)
	{
		printf("(%s) ", current->value);
	}
}

void	print_list(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current != NULL)
	{
		print_type(current);
		print_value(current);
		current = current->next;
	}
	printf("\n");
}
