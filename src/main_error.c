/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:23:18 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/09 18:05:20 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

char	*skip_whitespaces(char *cmdline)
{
	int	i;

	if (!cmdline)
		return (NULL);
	i = 0;
	while (cmdline[i] && is_whitespace(cmdline[i]))
		i++;
	return (cmdline + i);
}

int	check_for_syntax_error(t_token *cmdline, t_general *general)
{
	t_token	*node;

	node = cmdline;
	while (node)
	{
		if (node->type == PIPE && !ft_strlen(node->next->value))
		{
			general->exit_code = 2;
			print_error("minishell",
				"syntax error near unexpected token", NULL, "`|'");
			return (EXIT_FAILURE);
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
