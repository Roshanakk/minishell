/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_to_tab_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:13:01 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/01 18:16:02 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_exists(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

//nb de commandes (CAD de fragments contenant WORDs et VARs, 
//mais si fragment avec seulement REDIR_..., pas comptabilise)
int	ft_nb_of_cmds(t_token *cmdline)
{
	int	i;

	if (!cmdline)
		return (0);
	i = 0;
	while (cmdline)
	{
		while (cmdline && cmdline->type != WORD
			&& cmdline->type != VAR && cmdline->type != SQUOTE
			&& cmdline->type != DQUOTE)
			cmdline = cmdline->next;
		if (cmdline
			&& (cmdline->type == WORD || cmdline->type == VAR
				|| cmdline->type == SQUOTE || cmdline->type == DQUOTE))
			i++;
		while (cmdline
			&& (cmdline->type == WORD || cmdline->type == VAR
				|| cmdline->type == SQUOTE || cmdline->type == DQUOTE))
			cmdline = cmdline->next;
	}
	return (i);
}

int	ft_len_of_cmd(t_token *token)
{
	t_token	*tmp;
	size_t	len_of_cmd;

	tmp = token;
	len_of_cmd = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD || tmp->type == VAR
			|| tmp->type == SQUOTE || tmp->type == DQUOTE)
			len_of_cmd++;
		tmp = tmp->next;
	}
	return (len_of_cmd);
}
