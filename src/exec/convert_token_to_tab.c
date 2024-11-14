/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_to_tab.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:31:10 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/11 13:49:59 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_malloc_cmd_i(t_cmd *all_cmds_i, t_token *token)
{
	int	len_of_cmd;
	int	nb_of_redirs_in;
	int	nb_of_redirs_out;
	int	nb_of_redirs;

	len_of_cmd = ft_len_of_cmd(token);
	all_cmds_i->cmd = ft_calloc(sizeof(char *), len_of_cmd + 1);
	if (!all_cmds_i->cmd)
		return (EXIT_FAILURE);
	nb_of_redirs_in = ft_nb_of_redirs_in(token);
	nb_of_redirs_out = ft_nb_of_redirs_out(token);
	nb_of_redirs = nb_of_redirs_in + nb_of_redirs_out;
	all_cmds_i->redir = malloc(sizeof(char *) * (nb_of_redirs + 1));
	if (!(all_cmds_i->redir))
		return (EXIT_FAILURE);
	all_cmds_i->redir_type = malloc(sizeof(t_token_types) * (nb_of_redirs + 1));
	if (!(all_cmds_i->redir_type))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	deal_with_redir(int i, int *l, t_token *token, t_general *general)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (token->type == HEREDOC)
		ret = launch_heredoc(token->value, general);
	general->all_cmds[i].redir[*l] = token->value;
	general->all_cmds[i].redir_type[*l] = token->type;
	(*l)++;
	return (ret);
}

int	deal_with_word(int i, int *j, t_token *token, t_general *general)
{
	general->all_cmds[i].cmd[*j] = ft_strdup(token->value);
	(*j)++;
	return (EXIT_SUCCESS);
}

int	create_cmd_i_until_pipe(int i, t_token **token, t_general *general)
{
	int		l;
	int		j;
	t_token	*tmp;
	int		ret;

	l = 0;
	j = 0;
	tmp = *token;
	ret = EXIT_SUCCESS;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN || tmp->type == HEREDOC
			|| tmp->type == REDIR_OUT || tmp->type == APPEND)
			ret = deal_with_redir(i, &l, tmp, general);
		if (tmp->type == WORD
			|| tmp->type == SQUOTE || tmp->type == DQUOTE)
			ret = deal_with_word(i, &j, tmp, general);
		tmp = tmp->next;
	}
	general->all_cmds[i].cmd[j] = NULL;
	general->all_cmds[i].redir[l] = NULL;
	*token = tmp;
	return (ret);
}

int	convert_token_lst_to_tab(t_token *cmdline, t_general *general)
{
	t_token	*token;
	int		i;
	int		nb_of_cmds;
	int		ret;

	ret = EXIT_SUCCESS;
	if (!general || !cmdline)
		return (EXIT_FAILURE);
	nb_of_cmds = ft_nb_of_pipes(cmdline) + 1;
	general->all_cmds = malloc(sizeof(t_cmd) * nb_of_cmds);
	if (!general->all_cmds)
		return (EXIT_FAILURE);
	i = 0;
	token = cmdline;
	while (token)
	{
		if (ft_malloc_cmd_i(general->all_cmds + i, token))
			return (EXIT_FAILURE);
		ret = create_cmd_i_until_pipe(i, &token, general);
		i++;
		if (!token)
			break ;
		token = token->next;
	}
	return (ret);
}
