/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:06:47 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/08 14:44:36 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	if_quotes_and_default(t_token **token_node, int i)
{
	if (((*token_node)->value[i] == '\'' || (*token_node)->value[i] == '\"')
		&& (*token_node)->status == DEFAULT)
		return (true);
	else
		return (false);
}

void	change_status_to_quote(t_token **token_node, int *i)
{
	if ((*token_node)->value[*i] == '\'')
		(*token_node)->status = SQUOTE;
	if ((*token_node)->value[*i] == '\"')
		(*token_node)->status = DQUOTE;
	(*i)++;
}

bool	change_back_to_default(t_token **token_node, int *i)
{
	if (((*token_node)->value[*i] == '\''
			&& (*token_node)->status == SQUOTE)
		|| ((*token_node)->value[*i] == '\"'
			&& (*token_node)->status == DQUOTE))
	{
		(*token_node)->status = DEFAULT;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

int	count_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == DEFAULT)
		{
			if (str[i] == '\'')
				status = SQUOTE;
			if (str[i] == '\"')
				status = DQUOTE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SQUOTE)
			|| (str[i] == '\"' && status == DQUOTE))
		{
			status = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

bool	contains_quotes(const char *input_string)
{
	int	i;

	i = 0;
	if (!input_string)
		return (false);
	while (input_string[i] != '\0')
	{
		if (input_string[i] == '\"' || input_string[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}
