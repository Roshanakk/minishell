/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:04 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/01 18:16:21 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_failure_and_free(t_general *general)
{
	ft_free_general(general);
	exit(EXIT_FAILURE);
}

int	ft_nb_of_pipes(t_token *token)
{
	t_token	*tmp;
	size_t	nb_of_pipes;

	nb_of_pipes = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			nb_of_pipes++;
		tmp = tmp->next;
	}
	return (nb_of_pipes);
}

int	ft_nb_of_redirs_in(t_token *token)
{
	t_token	*tmp;
	size_t	nb_of_redirs_in;

	tmp = token;
	nb_of_redirs_in = 0;
	while (tmp && tmp->type != PIPE)
	{
		while (tmp && tmp->type != REDIR_IN
			&& tmp->type != HEREDOC && tmp->type != PIPE)
			tmp = tmp->next;
		while (tmp && (tmp->type == REDIR_IN || tmp->type == HEREDOC))
		{
			nb_of_redirs_in++;
			tmp = tmp->next;
		}
	}
	return (nb_of_redirs_in);
}

int	ft_nb_of_redirs_out(t_token *token)
{
	t_token	*tmp;
	size_t	nb_of_redirs_out;

	tmp = token;
	nb_of_redirs_out = 0;
	while (tmp && tmp->type != PIPE)
	{
		while (tmp && tmp->type != REDIR_OUT
			&& tmp->type != APPEND && tmp->type != PIPE)
			tmp = tmp->next;
		while (tmp && (tmp->type == REDIR_OUT || tmp->type == APPEND))
		{
			nb_of_redirs_out++;
			tmp = tmp->next;
		}
	}
	return (nb_of_redirs_out);
}
