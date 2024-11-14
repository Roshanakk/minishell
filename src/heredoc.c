/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:34:08 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/11 13:37:17 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	must_quit_heredoc(char *line, char *delimiter, t_general *general)
{
	if (g_sigtype == SIGINT)
	{
		general->exit_code = 130;
		return (EXIT_FAILURE);
	}
	if (!ft_strcmp(line, delimiter))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	deal_with_sigtype(t_general *general)
{
	if (g_sigtype != SIGINT)
	{
		print_error("minishell", "warning", NULL,
			"here-document delimited by end-of-file");
	}
	if (g_sigtype == SIGINT)
		general->exit_code = 130;
}

void	launch_heredoc_prompt(char *delimiter, t_general *general, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			deal_with_sigtype(general);
			break ;
		}
		if (must_quit_heredoc(line, delimiter, general))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	safe_close(fd, general);
}

int	launch_heredoc(char *delimiter, t_general *general)
{
	int		stdin_backup;

	if (!access("heredoc.tmp", F_OK))
		unlink("heredoc.tmp");
	stdin_backup = safe_dup(STDIN_FILENO, general);
	set_signals_heredoc();
	general->heredoc_fd = safe_open_heredoc("heredoc.tmp", general);
	general->exit_code = 0;
	launch_heredoc_prompt(delimiter, general, general->heredoc_fd);
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
	{
		ft_free_general(general);
		exit(EXIT_FAILURE);
	}
	safe_close(stdin_backup, general);
	set_signals_main();
	return (general->exit_code);
}
