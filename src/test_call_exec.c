/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_call_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:31:10 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/11/04 15:23:56 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// int	is_a_seperator(t_token *cmdline)
// {
// 	t_token *tmp;

// 	tmp = cmdline;
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE || tmp->type == HEREDOC || tmp->type == REDIR_IN
// 			|| tmp->type == REDIR_OUT || tmp->type == APPEND)
// 			return (1);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }


// int	ft_nb_pipes(t_token *cmdline)
// {
// 	int	i;
// 	t_token	*tmp;
// 	i = 0;
// 	tmp = cmdline;
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

int	ft_cmdline_size(t_token *cmdline)
{
	int	i;

	if (!cmdline)
		return (0);
	i = 0;
	while (cmdline)
	{
		while (cmdline && cmdline->type != WORD && cmdline->type != VAR)
			cmdline = cmdline->next;
		if (cmdline && (cmdline->type == WORD || cmdline->type == VAR))
			i++;
		while (cmdline && (cmdline->type == WORD || cmdline->type == VAR))
			cmdline = cmdline->next;
	}
	return (i);
}

// int	ft_malloc_cmd_features(t_general *general, int i)
// {
// 	int	len_of_cmd;

// 	//ft len_of_cmd
// 	len_of_cmd = 3;
// 	general->all_cmds[i].cmd = ft_calloc(sizeof(char *), len_of_cmd + 1);
// 	if (!(general->all_cmds[i].cmd))
// 		return (EXIT_FAILURE);
		
// 	// cmd_node->redir = malloc(sizeof(char *) * 1);
// 	// if (!(cmd_node->redir))
// 	// 	return (EXIT_FAILURE);

// 	// cmd_node->redir_type = malloc(sizeof(e_token_types) * 1);
// 	// if (!(cmd_node->redir_type))
// 	// 	return (EXIT_FAILURE);	
// 	return (EXIT_SUCCESS);
// }

int	file_exists(char *file_name)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	ft_len_of_cmd(t_token *token)
{
	t_token *tmp;
	size_t	len_of_cmd;

	tmp = token;
	len_of_cmd = 0;
	while (tmp && tmp->type != WORD)
		tmp = tmp->next;
	while (tmp && tmp->type == WORD)
	{
		len_of_cmd++;
		tmp = tmp->next;
	}
	return (len_of_cmd);
}

int ft_nb_of_redirs_in(t_token *token)
{
	t_token *tmp;
	size_t	nb_of_redirs_in;

	tmp = token;
	nb_of_redirs_in = 0;
	while (tmp && tmp->type != PIPE)
	{
		while (tmp && tmp->type != REDIR_IN && tmp->type != PIPE)
			tmp = tmp->next;
		while (tmp && tmp->type == REDIR_IN)
		{
			nb_of_redirs_in++;
			tmp = tmp->next;
		}
	}
	return (nb_of_redirs_in);	
}

int	ft_malloc_cmd_features(t_cmd *all_cmds_i, t_token *token)
{
	int	len_of_cmd;
	int	nb_of_redirs_in;
	int	nb_of_redirs_out;

	len_of_cmd = ft_len_of_cmd(token);
	all_cmds_i->cmd = ft_calloc(sizeof(char *), len_of_cmd + 1);
	if (!all_cmds_i->cmd)
		return (EXIT_FAILURE);
	
	nb_of_redirs_in = ft_nb_of_redirs_in(token);
	// nb_of_redirs_in = ft_nb_of_redirs_out(token);
	// cmd_node->redir = malloc(sizeof(char *) * 1);
	// if (!(cmd_node->redir))
	// 	return (EXIT_FAILURE);

	// cmd_node->redir_type = malloc(sizeof(e_token_types) * 1);
	// if (!(cmd_node->redir_type))
	// 	return (EXIT_FAILURE);	
	return (EXIT_SUCCESS);
}


//AJOUTER PROTECTIONS & FREE de protections

int read_token_lst(t_general *general, t_token *cmdline)
{
	t_token	*token;
	int		i;
	int 	len_of_cmd;
	int		j;
	int		l;

	int nb_of_cmds = ft_cmdline_size(cmdline);
	general->all_cmds = malloc(sizeof(t_cmd) * nb_of_cmds);
	if (!general->all_cmds)
		return (EXIT_FAILURE);

	i = 0;
	// l = 0;
	token = cmdline;
	while (token)
	{
		if (ft_malloc_cmd_features(general->all_cmds + i, token))
			return (EXIT_FAILURE);
		j = 0;
		while (token && token->type != PIPE)
		{
			
			// if (token->type == REDIR_IN)
			// {
			// 	general->all_cmds[i].redir[j] = token->value;
			// }
			
			if (token->type == WORD)
			{
				general->all_cmds[i].cmd[j] = token->value;
				j++;
			}

			token = token->next;
		}
		general->all_cmds[i].cmd[j] = NULL;
		i++;
		if (!token)
			break;
		token = token->next;
	}
}

void	ft_free_general(t_general *general)
{
	ft_token_lst_clear(&general->cmdline);
	// free(general->all_cmds->cmd);
	// ft_free_array(general->all_cmds->cmd, ft_array_size(general->all_cmds->cmd) - 1);
	// ft_free_array(general->all_cmds->redir, ft_array_size(general->all_cmds->redir) - 1);
	// free(general->all_cmds);
}

int main(int argc, char**argv, char **envp)
{
	t_general general;
 	general.cmdline = create_token_list("echo", REDIR_IN);
	// insert_at_end(&general.cmdline, "-n", WORD);
	// insert_at_end(&general.cmdline, "bonjour", WORD);
	// insert_at_end(&general.cmdline, "bonjour", PIPE);
	// insert_at_end(&general.cmdline, "helm", REDIR_IN);
	// insert_at_end(&general.cmdline, "rohan", REDIR_IN);

	// printf("%s - %d\n", general.cmdline->value, ft_nb_of_redirs_in(general.cmdline));
	// printf("%s - %d\n", general.cmdline->next->next->value, 
	// 	ft_nb_of_redirs_in(general.cmdline->next->next));
	
	// read_token_lst(&general, general.cmdline);

	// int i = 0;
	// while (general.all_cmds->cmd[i])
	// {
	// 	printf("%s\n", general.all_cmds->cmd[i]);
	// 	i++;
	// }
	
	ft_free_general(&general);

	return 0;
}



// int read_token_lst(t_general *general, t_token *cmdline)
// {
// 	t_token	*token;
// 	int		i;
// 	int 	len_of_cmd;
// 	int		j;
// 	int		l;

// 	int nb_of_cmds = ft_cmdline_size(cmdline);
// 	general->all_cmds = malloc(sizeof(t_cmd) * nb_of_cmds);
// 	if (!general->all_cmds)
// 		return (EXIT_FAILURE);

// 	i = 0;
// 	l = 0;
// 	token = cmdline;
// 	while (token)
// 	{
// 		// if (!ft_malloc_cmd_features(general->all_cmds + i))
// 		// 	return (EXIT_FAILURE);
// 		len_of_cmd = 3;
// 		general->all_cmds[i].cmd = ft_calloc(sizeof(char *), len_of_cmd);
// 		if (!(general->all_cmds[i].cmd))
// 			return (EXIT_FAILURE);
// 		// if (token->type == WORD)
// 		// {
// 		// 	general->all_cmds[i].cmd[l] = token->value;
// 		// 	l++;
// 		// }
// 		// general->all_cmds[i].cmd[l] = NULL;
// 		token = token->next;
// 		i++;
// 	}
// }

// void	ft_free_general(t_general *general)
// {
// 	ft_token_lst_clear(&general->cmdline);
// 	free(general->all_cmds->cmd);
// 	// ft_free_array(general->all_cmds->cmd, ft_array_size(general->all_cmds->cmd) - 1);
// 	// ft_free_array(general->all_cmds->redir, ft_array_size(general->all_cmds->redir) - 1);
// 	free(general->all_cmds);
// }

// int main(int argc, char**argv, char **envp)
// {
// 	t_general general;
//  	general.cmdline = create_token_list("echo", WORD);
// 	insert_at_end(&general.cmdline, "-n", WORD);
// 	insert_at_end(&general.cmdline, "bonjour", WORD);
// 	// insert_at_end(&general.cmdline, "edouard.txt", REDIR_OUT);

// 	// int nb_of_cmds = ft_cmdline_size(general.cmdline);
// 	// general.all_cmds = malloc(sizeof(t_cmd) * nb_of_cmds);
// 	// if (!(general.all_cmds))
// 	// 	return (EXIT_FAILURE);
// 	read_token_lst(&general, general.cmdline);
	
// 	ft_free_general(&general);

// 	return 0;
// }

