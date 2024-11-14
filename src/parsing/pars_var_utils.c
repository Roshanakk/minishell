/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_var_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:15:01 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/11 15:10:35 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_dollar(const char *input_string)
{
	if (input_string == NULL)
		return (0);
	if (ft_strchr(input_string, '$') != NULL)
		return (1);
	return (0);
}

int	deal_with_simple_quotes(char *word, char **join, int *i)
{
	char	*subword;
	int		start;

	start = *i;
	(*i)++;
	while (word[*i] && word[*i] != '\'')
		(*i)++;
	if (word[*i] && word[*i] == '\'')
		(*i)++;
	subword = ft_substr(word, start, *i - start);
	*join = ft_strjoin_and_free(*join, subword);
	free(subword);
	start = *i;
	return (start);
}

// void	browse_word(char *word, char **join, int *i, int *start)
// {
// 	pass_extra_quotes(word, join, i);
// 	*start = *i;
// 	while (word[*i] && word[*i] != '\"' && word[*i] != '\'' && word[*i] != ' ')
// 		(*i)++;
// 	if (word[*i] && (word[*i] == '\"' || word[*i] == '\'') && word[*i + 1])
// 		(*i)++;
// }

void	browse_word(char *word, char **join, int *i, int *start)
{
	pass_extra_quotes(word, join, i);
	*start = *i;
	while (word[*i] && word[*i] != '\"' && word[*i] != '\'' && word[*i] != ' ')
		(*i)++;
}

int	deal_with_double_quotes(char *word, char **join, int *i, t_general *general)
{
	char	*expanded_var;
	char	*subword;
	int		start;

	(*i)++;
	if (!word[*i] || (word[*i] == '\"' && word[*i + 1] && word[*i + 1] == '\"'))
	{
		*i = *i + 2;
		return (*i);
	}
	browse_word(word, join, i, &start);
	if (*i == start + 1)
		return (start);
	if (*i - 1 > 0)
	{
		subword = ft_substr(word, start, *i - start);
		expanded_var = expand_var(subword, general);
		join_var_and_d_quotes(join, expanded_var);
		free(expanded_var);
		free(subword);
	}
	pass_spaces(word, join, i);
	if (word[*i] && word[*i] == '\"')
		(*i)++;
	return (*i);
}

int	deal_with_characters(char *word, char **join, int *i, t_general *general)
{
	char	*expanded_var;
	char	*subword;
	int		start;

	start = *i;
	while (word[*i] && word[*i] != '\'' && word[*i] != '\"')
		(*i)++;
	subword = ft_substr(word, start, *i - start);
	expanded_var = expand_var(subword, general);
	*join = ft_strjoin_and_free(*join, expanded_var);
	free(subword);
	free(expanded_var);
	start = *i;
	return (start);
}
