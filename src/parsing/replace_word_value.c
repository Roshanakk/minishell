/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_word_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:43:58 by balacam           #+#    #+#             */
/*   Updated: 2023/12/11 15:24:32 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_word_value(t_token **head, t_general *general)
{
	t_token	*elem;
	char	*word;
	char	*join;
	int		i;
	int		start;

	elem = *head;
	while (elem)
	{
		if (elem->type == WORD && check_for_dollar(elem->value))
		{
			word = elem->value;
			init_values(&join, &i, &start);
			while (word[i])
				start = expand_if_needed(word, &join, &i, general);
			free(elem->value);
			elem->value = join;
		}
		elem = elem->next;
	}
	return (0);
}
