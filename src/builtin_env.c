/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:16:36 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/09 14:15:59 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// int	last_occurr_position(char *str, char c)
// {
// 	int	i;

// 	if (!str || !c)
// 		return (0);
// 	i = ft_strlen(str) - 1;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			return i;
// 		i--;
// 	}
// 	return (0);
// }

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

// char	*correct_env_path(char *path)
// {
// 	char	str[ft_strlen(path) + 2];
// 	int		i;

// 	i = 0;
// 	while (i < ft_strlen(path) + 2)
// 	{
// 		if (!i)
// 			str[i] = '_';
// 		else if (i == 1)
// 			str[i] = '=';
// 		else
// 			str[i] = path[i - 2];
// 		i++;
// 	}
// 	return (str);
// }

t_list	*create_envp_lst(char **envp)
{
	t_list	*envp_lst;
	int		i;
	char *tmp_0;
	char *tmp;
	char *path;

	envp_lst = ft_lstnew(envp[0], 0);
	i = 0;
	while (envp[++i])
	{
		// if (!ft_strncmp(envp[i], "PWD", 3))
		// {
		// 	tmp_0 = ft_strjoin(env_buffer, "PWD=");
		// 	free(env_buffer);
		// 	tmp = ft_strjoin(tmp_0, getcwd(NULL, 1024));
		// 	free(tmp_0);				
		// }
		if (!envp[i + 1])
		{
			tmp = get_path(envp, "env");
			path = ft_strjoin("_=", tmp);
			free(tmp);
			ft_lstadd_back(&envp_lst, ft_lstnew(path, i));
		}
		else
			ft_lstadd_back(&envp_lst, ft_lstnew(envp[i], i));
	}
	return (envp_lst);
}

int main(int argc, char **argv, char **envp)
{
	t_list	*envp_lst;

	// if (!ft_strcmp(argv[1], "env"))
		envp_lst = create_envp_lst(envp);
	int i = 0;
	t_list *tmp;
	tmp = envp_lst;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		if (!tmp->next)
			free(tmp->content);
		tmp= tmp->next;
	}
	ft_lstclear(&envp_lst);
	// free(envp_lst);
	return (0);
	
}

// int main(int argc, char **argv, char **envp)
// {
// 	char	*env_buffer;
// 	int		i;
// 	char *tmp_0;
// 	char *tmp;
// 	char *path;

// 	env_buffer = ft_strdup("\0");
// 	if (!ft_strcmp(argv[1], "env"))
// 	{
// 		i = -1;
// 		while (envp[++i])
// 		{
// 			// if (!ft_strncmp(envp[i], "PWD", 3))
// 			// {
// 			// 	tmp_0 = ft_strjoin(env_buffer, "PWD=");
// 			// 	free(env_buffer);
// 			// 	tmp = ft_strjoin(tmp_0, getcwd(NULL, 1024));
// 			// 	free(tmp_0);				
// 			// }
// 			if (!envp[i + 1])
// 			{
// 				tmp_0 = ft_strjoin(env_buffer, "_=");
// 				free(env_buffer);
// 				path = get_path(envp, "env");
// 				tmp = ft_strjoin(tmp_0, path);
// 				free(path);
// 				free(tmp_0);		
// 			}
// 			else
// 			{
// 				tmp = ft_strjoin(env_buffer, envp[i]);
// 				free(env_buffer);
// 			}
// 			env_buffer = ft_strjoin(tmp, "\n");
// 			free(tmp);
// 		}
// 		printf("%s", env_buffer);
// 	}
// 	free(env_buffer);
// 	return (0);
// }
