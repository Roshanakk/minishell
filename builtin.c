/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:16:36 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/04 11:17:40 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testshell.h"

int main(int argc, char **argv, char **envp)
{
	char	*env_buffer;
	int		i;
	char *tmp;

	env_buffer = ft_strdup("\0");
	if (ft_strcmp(argv[1], "env") == 0)
	{
		i = 0;
		while (envp[i])
		{
			
			tmp = ft_strjoin(env_buffer, envp[i]);
			free(env_buffer);
			env_buffer = ft_strjoin(tmp, "\n");
			free(tmp);
			i++;
		}
		printf("%s", env_buffer);
		free(env_buffer);
	}
	return (0);
}