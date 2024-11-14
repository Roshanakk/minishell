/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:04:58 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/08 11:40:03 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_and_print(char **env_tab)
{
	char	**dup_env;
	size_t	i;
	size_t	j;
	size_t	array_size;

	dup_env = env_tab;
	array_size = ft_array_size(dup_env);
	j = 0;
	while (j < array_size)
	{
		i = 0;
		while (i < array_size)
		{
			if (dup_env[i + 1] && ft_strcmp(dup_env[i], dup_env[i + 1]) > 0)
				ft_swap(&dup_env[i], &dup_env[i + 1]);
			i++;
		}
		j++;
	}
	print_export(dup_env);
}

static t_list	*node_in_env(t_list *lst, char *var_and_value)
{
	t_list	*tmp;
	size_t	len;

	tmp = lst;
	len = len_until_equal_sign(var_and_value);
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

/* arg[0] = "export" ; je recois les var d'env sans les guillemets */
int	add_to_env(t_general *general, char *var_and_value, int concatenate)
{
	t_list	*var_exists;
	t_list	*new_node;

	var_exists = node_in_env(general->env_lst, var_and_value);
	if (!var_exists)
	{
		new_node = ft_lstnew(ft_strdup(var_and_value));
		if (!new_node)
			return (EXIT_FAILURE);
		ft_lstadd_back(&(general->env_lst), new_node);
	}
	else
	{
		if (concatenate)
			var_exists->content = ft_strjoin_and_free(var_exists->content,
					ft_strchr_plus_one(var_and_value, '='));
		else
		{
			free(var_exists->content);
			var_exists->content = ft_strdup(var_and_value);
		}
		if (!var_exists->content)
			return (EXIT_FAILURE);
	}
	return (update_env(general));
}

// la condition "else if (len_until_equal_sign(args[i]) ...)" 
// permet de verifier qu'il y a un signe '=' 
// sans signe '=', pas d'export
int	run_export(char **args, t_general *general)
{
	int		i;
	int		concatenate;
	bool	error;

	error = false;
	if (!args[1] || !ft_strcmp(args[1], "-") || !ft_strcmp(args[1], "--"))
	{
		sort_and_print(general->env_tab);
		return (EXIT_SUCCESS);
	}
	i = 1;
	while (args[i])
	{
		if (deal_with_errors(args[i], &error) == 2)
			return (2);
		else if (len_until_equal_sign(args[i]) && is_not_underscore(args[i]))
		{
			concatenate = check_for_plus_sign(args[i]);
			add_to_env(general, args[i], concatenate);
		}
		i++;
	}
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
