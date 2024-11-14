/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:14:54 by balacam           #+#    #+#             */
/*   Updated: 2023/12/09 16:22:01 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	merge_value_append(t_token **head, t_general *general)
{
	t_token	*elem;
	t_token	*tmp;

	elem = *head;
	while (elem)
	{
		if (elem->type == APPEND && elem->next->value != NULL)
		{
			if (elem->next->type != WORD)
			{
				print_error("minishell",
					"syntax error near unexpected token ", NULL, elem->value);
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
