/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_call_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:31:10 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/11/06 15:49:08 by rraffi-k         ###   ########.fr       */
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

//nb de commandes (CAD de fragments contenant WORDs et VARs, mais si fragment avec seulement REDIR_..., pas comptabilise)
int	ft_nb_of_cmds(t_token *cmdline)
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

int	ft_nb_of_pipes(t_token *token)
{
	t_token *tmp;
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

int	ft_len_of_cmd(t_token *token)
{
	t_token *tmp;
	size_t	len_of_cmd;

	tmp = token;
	len_of_cmd = 0;
	while (tmp && tmp->type != WORD && tmp->type != VAR)
		tmp = tmp->next;
	while (tmp && (tmp->type == WORD || tmp->type == VAR))
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

int ft_nb_of_redirs_out(t_token *token)
{
	t_token *tmp;
	size_t	nb_of_redirs_out;

	tmp = token;
	nb_of_redirs_out = 0;
	while (tmp && tmp->type != PIPE)
	{
		while (tmp && tmp->type != REDIR_OUT && tmp->type != PIPE)
			tmp = tmp->next;
		while (tmp && tmp->type == REDIR_OUT)
		{
			nb_of_redirs_out++;
			tmp = tmp->next;
		}
	}
	return (nb_of_redirs_out);	
}

int	ft_malloc_cmd_i(t_cmd *all_cmds_i, t_token *token)
{
	int	len_of_cmd;
	int	nb_of_redirs_in;
	int	nb_of_redirs_out;

	len_of_cmd = ft_len_of_cmd(token);
	all_cmds_i->cmd = ft_calloc(sizeof(char *), len_of_cmd + 1);
	if (!all_cmds_i->cmd)
		return (EXIT_FAILURE);
	
	nb_of_redirs_in = ft_nb_of_redirs_in(token);
	nb_of_redirs_out = ft_nb_of_redirs_out(token);
	
	all_cmds_i->redir = malloc(sizeof(char *) * (nb_of_redirs_in + nb_of_redirs_out + 1));
	if (!(all_cmds_i->redir))
		return (EXIT_FAILURE);

	all_cmds_i->redir_type = malloc(sizeof(e_token_types) * (nb_of_redirs_in + nb_of_redirs_out + 1));
	if (!(all_cmds_i->redir_type))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


//AJOUTER PROTECTIONS & FREE de protections

int convert_token_lst_to_tab(t_general *general, t_token *cmdline)
{
	t_token	*token;
	int		i;
	int 	len_of_cmd;
	int		j;
	int		l;
	int		nb_of_cmds;

	if (!cmdline)
		return(EXIT_FAILURE);
	nb_of_cmds = ft_nb_of_pipes(cmdline) + 1;
	general->all_cmds = malloc(sizeof(t_cmd) * nb_of_cmds);
	if (!general->all_cmds)
		ft_exit(general, EXIT_FAILURE);

	i = 0;
	token = cmdline;
	while (token)
	{
		if (ft_malloc_cmd_i(general->all_cmds + i, token))
			ft_exit(general, EXIT_FAILURE);
		l = 0;
		j = 0;
		while (token && token->type != PIPE)
		{
			//AJOUTER ERREUR SI REDIR_IN N'EXISTE PAS
			if (token->type == REDIR_IN || token->type == REDIR_OUT)
			{
				general->all_cmds[i].redir[l] = token->value;
				general->all_cmds[i].redir_type[l] = token->type;
				l++;
			}	
			else if (token->type == WORD)
			{
				general->all_cmds[i].cmd[j] = token->value;
				j++;
			}
			else if (token->type == VAR)
			{
				general->all_cmds[i].cmd[j] = getenv(token->value);
				j++;
			}
			token = token->next;
		}
		general->all_cmds[i].cmd[j] = NULL;
		general->all_cmds[i].redir[l] = NULL;
		i++;
		if (!token)
			break;
		token = token->next;
	}
}




// int main(int argc, char**argv, char **envp)
// {
// 	t_general general;

// 	general = (t_general){0};
//  	general.cmdline = create_token_list("UUUSER", VAR);
// 	// insert_at_end(&general.cmdline, "OKKK", VAR);
// 	insert_at_end(&general.cmdline, "echo", WORD);
// 	insert_at_end(&general.cmdline, "-n", WORD);
// 	insert_at_end(&general.cmdline, "bonjour", WORD);
// 	// insert_at_end(&general.cmdline, "USER", VAR);
// 	// insert_at_end(&general.cmdline, "|", PIPE);
// 	// insert_at_end(&general.cmdline, "outfile", REDIR_OUT);
// 	// insert_at_end(&general.cmdline, "echo", WORD);

	
// 	convert_token_lst_to_tab(&general, general.cmdline);

// 	int i = 0;
// 	int j;
// 	int len_of_cmd;
// 	t_token *tmp;
// 	tmp = general.cmdline;
// 	// while (general.all_cmds[i].cmd[0])
// 	while (i < ft_nb_of_pipes(general.cmdline) + 1)
// 	{
// 		j = 0;
// 		len_of_cmd = ft_len_of_cmd(tmp);
// 		// while (general.all_cmds[i].cmd[j])
// 		while (j < len_of_cmd)
// 		{
// 			printf("cmd : %s\n", general.all_cmds[i].cmd[j]);
// 			j++;
// 			tmp = tmp->next;
// 		}
// 		printf("cmd i finie\n");
// 		i++;
// 	}

// 	ft_free_general(&general);

// 	return 0;
// }
