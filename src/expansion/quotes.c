/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:47:26 by balacam           #+#    #+#             */
/*   Updated: 2023/12/08 14:42:37 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_quotes(t_token **token_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_len((*token_node)->value, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->value[i])
	{
		if (if_quotes_and_default(token_node, i) == true)
		{
			change_status_to_quote(token_node, &i);
			continue ;
		}
		else if (change_back_to_default(token_node, &i) == true)
			continue ;
		new_line[j++] = (*token_node)->value[i++];
	}
	new_line[j] = '\0';
	free_ptr((*token_node)->value);
	(*token_node)->value = new_line;
	return (0);
}

int	handle_quotes(t_general *general)
{
	t_token	*elem;

	elem = general->cmdline;
	while (elem)
	{
		if (contains_quotes(elem->value) == true)
			remove_quotes(&elem);
		elem = elem->next;
	}
	return (0);
}
