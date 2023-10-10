/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:16:36 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/10 12:33:01 by rraffi-k         ###   ########.fr       */
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
		path_exec = ft_strjoin(path_part, cmd);
		if (!path_exec)
			return (NULL);
		free(path_part);
		if (access(path_exec, F_OK) == 0)
			return (ft_free_double_char(all_paths, ft_cmpt(getenv("PATH"), ':')), path_exec);
		free(path_exec);
	}
	ft_free_double_char(all_paths, ft_cmpt(getenv("PATH"), ':'));
	return (NULL);
}

void	create_envp_lst(char **envp, t_list **envp_lst)
{
	int		i;
	char 	*envp_i;
	char 	*path;
	char	*tmp;

	*envp_lst = ft_lstnew(ft_strdup(envp[0]), 0);
	i = 0;
	while (envp[++i])
		ft_lstadd_back(envp_lst, ft_lstnew(ft_strdup(envp[i]), i));
}

int main(int argc, char **argv, char **envp)
{
	t_list	*envp_lst;

	// if (!ft_strcmp(argv[1], "env"))
		// envp_lst = create_envp_lst(envp);
		create_envp_lst(argv, &envp_lst);
	int i = 0;
	t_list *tmp;
	tmp = envp_lst;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&envp_lst);
	return (0);
	
}
