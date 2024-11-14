/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_var_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:07:54 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/11 13:44:11 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_values(char **join, int *i, int *start)
{
	*join = ft_strdup("\0");
	*start = 0;
	*i = 0;
}

void	pass_extra_quotes(char *word, char **join, int *i)
{
	while (word[*i] && (word[*i] == '\'' || word[*i] == ' '))
	{
		if (word[*i] == '\'')
			*join = ft_strjoin_and_free(*join, "\'");
		else if (word[*i] == ' ')
			*join = ft_strjoin_and_free(*join, " ");
		(*i)++;
	}	
}

void	pass_spaces(char *word, char **join, int *i)
{
	while (word[*i] && word[*i] == ' ')
	{
		*join = ft_strjoin_and_free(*join, " ");
		(*i)++;
	}
}

void	join_var_and_d_quotes(char **join, char *expanded_var)
{
	*join = ft_strjoin_and_free(*join, expanded_var);
}

char	*first_dollars(char *subword, int *i)
{
	char	*join;

	while (subword[*i] && subword[*i] == '$'
		&& (!subword[*i + 1] || subword[*i + 1] == '$'))
	{
		if (*i == 0)
			join = ft_strdup("\0");
		join = ft_strjoin_and_free(join, "$");
		(*i)++;
	}
	return (join);
}
