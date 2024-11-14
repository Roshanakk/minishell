/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:15:01 by balacam           #+#    #+#             */
/*   Updated: 2023/12/09 15:27:52 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	merge_value_heredoc(t_token **head, t_general *general)
{
	t_token	*elem;
	t_token	*tmp;

	elem = *head;
	while (elem)
	{
		if (elem->type == HEREDOC)
		{
			if (elem->next->type != WORD)
			{
				printf("%s %s\n", "minishell",
					"syntax error near unexpected token `newline'");
				general->exit_code = 2;
				elem->value = NULL;
				return (-2);
			}
			tmp = elem->next;
			free(elem->value);
			elem->value = elem->next->value;
			elem->next = elem->next->next;
			free(tmp);
		}
		elem = elem->next;
	}
	return (0);
}
