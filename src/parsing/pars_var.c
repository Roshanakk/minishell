/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:15:15 by balacam           #+#    #+#             */
/*   Updated: 2023/12/11 14:01:18 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*deal_with_first_var(char *subword, char *first_var, t_general *general)
{
	char	*join;
	int		i;

	if (subword[0] == '$')
	{
		i = 0;
		join = first_dollars(subword, &i);
		if (!subword[i])
			return (join);
		if (first_var && !ft_strcmp(first_var, "?"))
			join = ft_itoa(general->exit_code);
		else if (get_value_in_env(first_var, general->env_tab))
			join = ft_strdup(get_value_in_env(first_var,
						general->env_tab));
		else
			join = ft_strdup("\0");
	}
	else
		join = ft_strdup(first_var);
	return (join);
}

char	*expand_exit_code(char *join, t_general *general)
{
	char	*exit_code;

	exit_code = ft_itoa(general->exit_code);
	join = ft_strjoin_and_free(join, exit_code);
	free(exit_code);
	return (join);
}

char	*expand_valid_identifier(char *join, char *var, t_general *general)
{
	char	*expanded_var;

	expanded_var = get_value_in_env(var, general->env_tab);
	join = ft_strjoin_and_free(join, expanded_var);
	return (join);
}

char	*expand_var(char *subword, t_general *general)
{
	char	**vars;
	char	*join;
	int		i;

	vars = ft_split(subword, '$');
	join = deal_with_first_var(subword, vars[0], general);
	i = 1;
	while (vars[i])
	{
		if (!ft_strcmp(vars[i], "?"))
			join = expand_exit_code(join, general);
		else if (check_valid_identifier(vars[i]))
			join = expand_valid_identifier(join, vars[i], general);
		else
			join = ft_strdup(vars[i]);
		i++;
	}
	ft_free_array(vars, ft_array_size(vars));
	return (join);
}

/*
char	*expand_var(char *subword, t_general *general)
{
	char	**vars;
	char	*join;
	char	*exit_code;
	char	*expanded_var;
	int		i;

	vars = ft_split(subword, '$');
	join = deal_with_first_var(subword, vars[0], general);
	i = 1;
	while (vars[i])
	{
		if (!ft_strcmp(vars[i], "?"))
		{
			exit_code = ft_itoa(general->exit_code);
			join = ft_strjoin_and_free(join, exit_code);
			free(exit_code);
		}
		else if (check_valid_identifier(vars[i]))
		{
			expanded_var = get_value_in_env(vars[i], general->env_tab);
			join = ft_strjoin_and_free(join, expanded_var);
		}
		i++;
	}
	ft_free_array(vars, ft_array_size(vars));
	return (join);
}
*/

int	expand_if_needed(char *word, char **join, int *i, t_general *general)
{
	int	start;

	if (word[*i] && word[*i] == '\'')
		start = deal_with_simple_quotes(word, join, i);
	else if (word[*i] && word[*i] == '\"')
		start = deal_with_double_quotes(word, join, i, general);
	else
		start = deal_with_characters(word, join, i, general);
	return (start);
}
