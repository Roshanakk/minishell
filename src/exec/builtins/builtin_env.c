/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:16:36 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/06 15:16:20 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_in_env(char *var_name, char **env_tab)
{
	int		len_var_name;
	int		i;
	int		len;

	if (!var_name || !env_tab)
		return (NULL);
	len_var_name = ft_strlen(var_name);
	i = 0;
	while (env_tab[i])
	{
		len = 0;
		while (env_tab[i][len] && env_tab[i][len] != '=')
			len++;
		if (len == len_var_name
			&& !ft_strncmp(var_name, env_tab[i], len_var_name))
			return (ft_strchr_plus_one(env_tab[i], '='));
		i++;
	}
	return (NULL);
}

char	*get_path(char **env_tab, char *cmd)
{
	int		i;
	char	**all_paths;
	char	*path_part;
	char	*path_exec;

	all_paths = ft_split(get_value_in_env("PATH", env_tab), ':');
	if (!all_paths)
		return (NULL);
	i = -1;
	while (all_paths[++i])
	{
		path_part = ft_strjoin(all_paths[i], "/");
		if (!path_part)
			return (NULL);
		path_exec = ft_strjoin_and_free(path_part, cmd);
		if (!path_exec)
			return (NULL);
		if (access(path_exec, F_OK) == 0)
			return (ft_free_array(all_paths, ft_cmpt(getenv("PATH"), ':')),
				path_exec);
		free(path_exec);
	}
	ft_free_array(all_paths, ft_cmpt(getenv("PATH"), ':'));
	return (NULL);
}

//A GERER : PWD ET OLDPWD
int	create_env_lst(char **envp, t_general *general)
{
	int		i;
	char	*envp_i;
	t_list	*new_node;

	if (!envp[0] || !envp[0][0])
		return (EXIT_FAILURE);
	i = 0;
	envp_i = ft_strdup(envp[i]);
	if (!envp_i)
		return (EXIT_FAILURE);
	general->env_lst = ft_lstnew(envp_i);
	if (!general->env_lst)
		return (EXIT_FAILURE);
	while (envp[++i])
	{
		envp_i = ft_strdup(envp[i]);
		if (!envp_i)
			return (EXIT_FAILURE);
		new_node = ft_lstnew(envp_i);
		if (!new_node)
			return (EXIT_FAILURE);
		ft_lstadd_back(&(general->env_lst), new_node);
	}
	return (EXIT_SUCCESS);
}

int	convert_env_to_tab(t_general *general)
{
	int		i;
	t_list	*node;

	general->env_tab = ft_calloc(sizeof(char *),
			ft_lstsize(general->env_lst) + 1);
	if (!general->env_tab)
		return (EXIT_FAILURE);
	i = 0;
	node = general->env_lst;
	while (node)
	{
		general->env_tab[i] = ft_strdup(node->content);
		if (!general->env_tab[i])
			return (EXIT_FAILURE);
		i++;
		node = node->next;
	}
	general->env_tab[i] = NULL;
	return (EXIT_SUCCESS);
}

int	run_env(t_general *general)
{
	int	i;

	i = 0;
	while (i < ft_lstsize(general->env_lst))
	{
		printf("%s\n", general->env_tab[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
