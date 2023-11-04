/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:16:36 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/11/04 19:08:34 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char *get_path(char **envp, char *cmd)
{
	int	i;
	char	**all_paths;
	char	*path_part;
	char	*path_exec;
	char	*tmp;

	all_paths = ft_split(getenv("PATH"), ':');
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
		// free(path_part);
		if (access(path_exec, F_OK) == 0)
			return (ft_free_array(all_paths, ft_cmpt(getenv("PATH"), ':')), path_exec);
		free(path_exec);
	}
	ft_free_array(all_paths, ft_cmpt(getenv("PATH"), ':'));
	return (NULL);
}

//A GERER : PWD ET OLDPWD

int	create_env_lst(char **envp, t_general *general)
{
	int		i;
	char 	*envp_i;
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
// IL MANQUE LE FREE LST DE LA PROTECTION
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

	general->env_tab = ft_calloc(sizeof(char *), ft_lstsize(general->env_lst) + 1);
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

// int main(int argc, char **argv, char **envp)
// {
// 	t_general	general;

// 	general = (t_general){0};
// 	// if (!ft_strcmp(argv[1], "env"))
// 		// env->lst = create_env->lst(envp);
// 	// printf("OK");
// 	if (create_env_lst(envp, &general))
// 		return (EXIT_FAILURE);
// 	if (convert_env_to_tab(&general))
// 		return (ft_lstclear(&(general.env_lst)), EXIT_FAILURE);
	
// 	int i = 0;
// 	while (i < ft_lstsize(general.env_lst))
// 	{
// 		printf("%s\n", general.env_tab[i]);
// 		i++;
// 	}
// 	ft_free_array(general.env_tab, ft_lstsize(general.env_lst) - 1);
// 	ft_lstclear(&(general.env_lst));
// 	return (0);
	
// }
