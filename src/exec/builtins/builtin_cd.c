/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:38:49 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/06 15:00:20 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir(char **cmd, t_general *general)
{
	char	*dir;

	dir = NULL;
	if (!cmd[1] || !ft_strlen(cmd[1])
		|| !ft_strcmp(cmd[1], "~") || !ft_strcmp(cmd[1], "--"))
	{
		dir = get_value_in_env("HOME", general->env_tab);
		if (!dir)
		{
			print_error("minishell", "cd", NULL, "HOME not set");
			general->exit_code = 1;
		}
	}
	else if (cmd[1] && !ft_strcmp(cmd[1], "-"))
	{
		dir = get_value_in_env("OLDPWD", general->env_tab);
		if (!dir)
		{
			print_error("minishell", "cd", NULL, "OLDPWD not set");
			general->exit_code = 1;
		}
	}
	else
		dir = cmd[1];
	return (dir);
}

//Identique a fonction node_in_env de builtin_export
//sauf qu'on ignore le fait qu'il n'y a pas de signe =
static t_list	*node_in_env(t_list *lst, char *var_and_value)
{
	t_list	*tmp;
	size_t	len;

	tmp = lst;
	len = ft_strlen(var_and_value);
	tmp = lst;
	while (tmp)
	{
		if ((len == len_until_equal_sign(tmp->content))
			&& !ft_strncmp(tmp->content, var_and_value, len))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	set_env(char *var_name, char *new_var_value, t_general *general)
{
	t_list	*var_node;
	char	*new_content;
	char	*var_name_with_equal_sign;

	var_node = node_in_env(general->env_lst, var_name);
	if (!var_node)
		return (EXIT_FAILURE);
	var_name_with_equal_sign = ft_strjoin(var_name, "=");
	new_content = ft_strjoin(var_name_with_equal_sign, new_var_value);
	free(var_name_with_equal_sign);
	if (!new_content)
		return (EXIT_FAILURE);
	else
	{
		free(var_node->content);
		var_node->content = new_content;
		if (!var_node->content)
		{
			ft_free_general(general);
			exit(1);
		}
	}
	ft_free_array(general->env_tab, ft_array_size(general->env_tab));
	convert_env_to_tab(general);
	return (EXIT_SUCCESS);
}

int	update_pwd(t_general *general)
{
	char	buffer[MAX_PATH_LEN];

	if (set_env("OLDPWD", get_value_in_env("PWD", general->env_tab), general))
	{
		print_error("minishell", "cd", NULL, "OLDPWD not set");
		return (EXIT_FAILURE);
	}
	if (set_env("PWD", getcwd(buffer, MAX_PATH_LEN), general))
	{
		print_error("minishell", "cd", NULL, "PWD not set");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	run_cd(char **cmd, t_general *general)
{
	char	*dir;

	if (cmd[0] && cmd[1] && cmd[2])
	{
		print_error("minishell", "cd", NULL, "too many arguments");
		return (EXIT_FAILURE);
	}
	dir = get_dir(cmd, general);
	if (!dir)
		return (EXIT_FAILURE);
	if (chdir(dir) == -1)
	{
		print_error("minishell", "cd", dir, "No such file or directory");
		return (EXIT_FAILURE);
	}
	return (update_pwd(general));
}
