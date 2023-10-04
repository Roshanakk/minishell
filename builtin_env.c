/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:16:36 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/04 14:19:11 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testshell.h"

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

int main(int argc, char **argv, char **envp)
{
	char	*env_buffer;
	int		i;
	char *tmp_0;
	char *tmp;
	char *path;

	env_buffer = ft_strdup("\0");
	if (!ft_strcmp(argv[1], "env"))
	{
		i = -1;
		while (envp[++i])
		{
			if (!envp[i + 1])
			{
				tmp_0 = ft_strjoin(env_buffer, "_=");
				free(env_buffer);
				path = get_path(envp, "env");
				tmp = ft_strjoin(tmp_0, path);
				free(path);
				free(tmp_0);		
			}
			else
			{
				tmp = ft_strjoin(env_buffer, envp[i]);
				free(env_buffer);
			}
			env_buffer = ft_strjoin(tmp, "\n");
			free(tmp);
		}
		printf("%s", env_buffer);
	}
	free(env_buffer);
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char *res;
// 	res = get_path(envp, "env");
// 	printf("%s\n", res);
// 	free(res);
// 	// printf("%s\n", getenv("PATH"));
	
// }