/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:52:41 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/09 15:52:55 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	must_close_previous_file(char **redir, enum token_types *redir_type, int i)
{
	if (redir[i + 1] && redir_type[i + 1])
	{
		if (redir_type[i] == REDIR_OUT && redir_type[i + 1] == REDIR_OUT)
			return (1);
		if ((redir_type[i] == REDIR_IN || redir_type[i] == HEREDOC)
			&& (redir_type[i + 1] == REDIR_IN || redir_type[i + 1] == HEREDOC))
			return (1);
	}
	return (0);
}

int	contains_type_redir_in(char **redir, t_token_types *redir_type)
{
	size_t	i;

	i = 0;
	while (i < ft_array_size(redir))
	{
		if (redir_type[i] == REDIR_IN || redir_type[i] == HEREDOC)
			return (1);
		i++;
	}
	return (0);
}

int	contains_type_out_or_append(char **redir, t_token_types *redir_type)
{
	size_t	i;

	i = 0;
	while (i < ft_array_size(redir))
	{
		if (redir_type[i] == REDIR_OUT || redir_type[i] == APPEND)
			return (1);
		i++;
	}
	return (0);
}
