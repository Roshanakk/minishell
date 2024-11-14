/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:09:09 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/11 13:39:09 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	g_sigtype;

void	deal_with_sigint(t_general *general)
{
	if (g_sigtype == SIGINT)
	{
		general->exit_code = 130;
		g_sigtype = SIGEMPTY;
	}	
}

void	launch_minishell_prompt(t_general *general)
{
	char	*cmdline;
	int		token_lst;

	while (1)
	{
		set_signals_main();
		cmdline = readline("minishell: ");
		deal_with_sigint(general);
		cmdline = skip_whitespaces(cmdline);
		if (!cmdline)
			break ;
		if (!cmdline[0])
			continue ;
		add_history(cmdline);
		token_lst = tokenization(general, cmdline);
		if (check_for_syntax_error(general->cmdline, general)
			|| sanitize_lst_tokens(general->cmdline, general) == EXIT_FAILURE)
		{
			ft_token_lst_clear(&general->cmdline);
			continue ;
		}
		minishell(general);
		ft_free_all_but_env(general);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_general	general;

	(void) argc;
	(void) argv;
	general = (t_general){0};
	general.exit_code = 0;
	g_sigtype = SIGEMPTY;
	if (create_env_lst(envp, &general))
		return (EXIT_FAILURE);
	if (convert_env_to_tab(&general))
		return (ft_lstclear(&(general.env_lst)), EXIT_FAILURE);
	launch_minishell_prompt(&general);
	ft_free_env(&general);
}
