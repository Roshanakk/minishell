/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:16:36 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/19 18:28:59 by rraffi-k         ###   ########.fr       */
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
int	create_env_lst(char **envp, t_envp *env)
{
	int		i;
	char 	*envp_i;
	t_list	*new_node;

	i = 0;

	envp_i = ft_strdup(envp[i]);
	if (!envp_i)
		return (EXIT_FAILURE);
	env->lst = ft_lstnew(envp_i);
	if (!env->lst)
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
		ft_lstadd_back(&(env->lst), new_node);
	}
	return (EXIT_SUCCESS);
}

//A APPELER POUR MAJ (POUR CHAQUE MODIF DE ENV)
int	convert_env_to_tab(t_envp *env)
{
	int		i;
	t_list	*node;

	env->tab = malloc(sizeof(char *) * ft_lstsize(env->lst));
	if (!env->tab)
		return (EXIT_FAILURE);
	i = 0;
	node = env->lst;
	while (node)
	{
		env->tab[i] = ft_strdup(node->content);
		if (!env->tab[i])
			return (EXIT_FAILURE);
		i++;
		node = node->next;
	}
	return (EXIT_SUCCESS);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_envp	env;

// 	// if (!ft_strcmp(argv[1], "env"))
// 		// env->lst = create_env->lst(envp);
// 	// printf("OK");
// 	if (create_env_lst(envp, &env))
// 		return (EXIT_FAILURE);
// 	if (convert_env_to_tab(&env))
// 		return (ft_lstclear(&(env.lst)), EXIT_FAILURE);
	
// 	int i = 0;
// 	while (i < ft_lstsize(env.lst))
// 	{
// 		printf("%s\n", env.tab[i]);
// 		i++;
// 	}
// 	ft_free_array(env.tab, ft_lstsize(env.lst) - 1);
// 	ft_lstclear(&(env.lst));
// 	return (0);
	
// }
