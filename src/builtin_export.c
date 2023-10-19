/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:04:58 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/19 20:35:49 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//que faire de la derniere variable _= ?
void	print_export(char **dup_env)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (dup_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		flag = 1;
		j = 0;
		while (dup_env[i][j])
		{
			ft_putchar_fd(dup_env[i][j], 1);
			if (dup_env[i][j] == '=' && flag)
			{
				ft_putchar_fd('"', 1);
				flag--;
			}
			j++;
		}
		if (!flag)
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	sort_and_print(char **env_tab)
{
	char	**dup_env;
	int	i;
	int	j;
	size_t	array_size;
	char *tmp;

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

int	check_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

//MODIFIER : rogner a '='
t_list	*node_in_env(t_list *lst, char *var_and_value)
{
	t_list *tmp;
	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->content, var_and_value))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/* arg[0] = "export" ; je recois les var d'env sans les guillemets */

int	add_to_env(t_envp *env, char *var_and_value, int concatenate)
{
	int	i;
	t_list *var_exists;
	t_list	*new_node;

	var_exists = node_in_env(env->lst, var_and_value);
	i = 0;
	if (!var_exists)
	{
		new_node = ft_lstnew(ft_strdup(var_and_value));
		if (!new_node)
			return (EXIT_FAILURE);
		ft_lstadd_back(&(env->lst), new_node);
	}
	else
	{
		if (concatenate)
			var_exists->content = ft_strjoin_and_free(var_exists->content, ft_strchr_plus_one(var_and_value, '='));
		else
		{
			free(var_exists->content);
			var_exists->content = ft_strdup(var_and_value);
		}
		if (!var_exists->content)
			return (EXIT_FAILURE);
	}
	// ft_free_array(env->tab, ft_array_size(env->tab));
	// convert_env_to_tab(env);
	return (EXIT_SUCCESS);
}

int	check_for_plus_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i - 1] && str[i - 1] == '+')
		return (1);
	return (0);
}


// ACTUALISER ENV_TAB AVANT DE FAIRE EXPORT
int run_export(char **args, t_envp *env)
{
	int	i;
	int concatenate;

	if (!args[1])
	{
		sort_and_print(env->tab);
		return (1);
	}
	i = 0;
	while (args[i])
	{
		if (!check_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 1);
			ft_putstr_fd(args[i], 1);
			ft_putstr_fd("`: not a valid identifier\n", 1);
		}
		else
		{
			concatenate = check_for_plus_sign(args[i]);
			add_to_env(env, args[i], concatenate);
		}
		i++;
	}
	return (1);
}



int main(int argc, char **argv, char **envp)
{
	// t_list *first_node = ft_lstnew(ft_strdup("OK=bonjour"));
	// ft_lstadd_back(&first_node, ft_lstnew(ft_strdup("HELLO=quoi")));
	// ft_lstadd_back(&first_node, ft_lstnew(ft_strdup("VAR3=hey")));
	// add_to_env(first_node, "VAR2=essai", 0);
	// add_to_env(first_node, "VAR2=essai", 1);
	// t_list *tmp = first_node;
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->content);
	// 	tmp = tmp->next;
	// }
	// ft_lstclear(&first_node);
	

	t_envp env;

	// printf("%zu\n", ft_array_size(argv));
	if (create_env_lst(argv + 1, &env))
		return (EXIT_FAILURE);
	if (convert_env_to_tab(&env))
		return (ft_lstclear(&(env.lst)), EXIT_FAILURE);

	add_to_env(&env, "OK=oui", 0);
	t_list *tmp = env.lst;
	
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	// if (!ft_strcmp(argv[1], "export"))
	// 	run_export(argv + 1, &env);
	// ft_lstadd_back(&env.lst, ft_lstnew(ft_strdup("OKKKKK")));
	// ft_free_array(env.tab, ft_array_size(env.tab));
	// if (convert_env_to_tab(&env))
	// 	return (ft_lstclear(&(env.lst)), EXIT_FAILURE);

	// sort_and_print(env.tab);
	// ft_test(env.tab);
	// printf("%zu\n", ft_array_size(env.tab));

	ft_free_array(env.tab, ft_array_size(env.tab));
	// ft_free_array(env.tab, ft_lstsize(env.lst) - 1);
	ft_lstclear(&(env.lst));

}

