/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:04:58 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/17 14:26:32 by rraffi-k         ###   ########.fr       */
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

	dup_env = env_tab;
	j = 0;
	while (j < ft_array_size(dup_env))
	{
		i = 0;
		while (i < ft_array_size(dup_env))
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

t_list	*var_node_exists(t_list *lst, char *var_and_value)
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

// int	add_to_env(t_envp *env, char *var_and_value, int concatenate)
// {
// 	int	i;
// 	t_list *var_exists;
// 	t_list	*new_node;

// 	var_exists = var_node_exists(env->lst, var_and_value);
// 	i = 0;
// 	if (!var_exists)
// 	{
// 		new_node = ft_lstnew(var_exists->content);
// 		if (!new_node)
// 			return (EXIT_FAILURE);
// 		ft_lstadd_back(&env, new_node);
// 	}
// 	else
// 	{
// 		if (concatenate)
// 			var_exists->content = ft_strjoin(var_exists->content, ft_strchr(var_and_value, '='));
// 		else
// 		{
// 			free(var_exists->content);
// 			var_exists->content = ft_strdup(var_and_value);
// 		}
// 		if (!var_exists->content)
// 			return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// 	//free env->tab et reappeler conv_env_to_tab ?
// }


/* arg[0] = "export" ; je recois les var d'env sans les guillemets */
// int run_export(char **args, t_envp *env)
// {
// 	int	i;
// 	int concatenate;

// 	concatenate = 0;
// 	if (!args[1])
// 	{
// 		sort_and_print(env->tab);
// 		return (1);
// 	}
// 	i = 0;
// 	while (args[i])
// 	{
// 		if (!check_valid_identifier(args[i]))
// 		{
// 			ft_putstr_fd("minishell: export: `", 1);
// 			ft_putstr_fd(args[i], 1);
// 			ft_putstr_fd("`: not a valid identifier\n", 1);
// 		}
// 		i++;
// 		//CONCATENATE ?
// 		add_to_env(env, args[i], concatenate);
// 	}
// 	return (1);
// }

int	add_to_env(t_list *env_lst, char *var_and_value, int concatenate)
{
	int	i;
	t_list *var_exists;
	t_list	*new_node;

	var_exists = var_node_exists(env_lst, var_and_value);
	i = 0;
	if (!var_exists)
	{
		new_node = ft_lstnew(var_and_value);
		if (!new_node)
			return (EXIT_FAILURE);
		ft_lstadd_back(&env_lst, new_node);
	}
	else
	{
		if (concatenate)
			var_exists->content = ft_strjoin(var_exists->content, ft_strchr(var_and_value, '='));
		else
		{
			var_exists->content = NULL;
			// free(var_exists);
			var_exists->content = var_and_value;
		}
		if (!var_exists->content)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
	//free env->tab et reappeler conv_env_to_tab ?
}

int main(int argc, char **argv, char **env)
{
	t_list *first_node = ft_lstnew("OK=bonjour");
	
	ft_lstadd_back(&first_node, ft_lstnew("HELLO=quoi"));
	ft_lstadd_back(&first_node, ft_lstnew("VAR3=hey"));

	add_to_env(first_node, "VAR2=essai", 0);
	add_to_env(first_node, "VAR2=essai", 0);
	t_list *tmp = first_node;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&first_node);
	// t_envp *env;

	// run_export(argv);
	// sort(new_argv);
	// int i = 0;
	// while (new_argv[i])
	// {
	// 	printf("%s\n", new_argv[i]);
	// 	i++;
	// }
	// ft_free_array(new_argv, ft_array_size(new_argv));
}


// char **dup_array(char **array)
// {
// 	char	**dup;
// 	int		i;

// 	dup = malloc(sizeof(char *) * ft_array_size(array));
// 	if (!dup)
// 		return (NULL);
// 	i = 0;
// 	while (i < ft_array_size(array))
// 	{
// 		dup[i] = ft_strdup(array[i]);
// 		if (!dup[i])
// 			return (ft_free_array(dup, i));
// 		i++;
// 	}
// 	return (dup);
// }

// void	ft_swap(char **a, char **b)
// {
// 	char	*a1;

// 	a1 = *a;
// 	*a = *b;
// 	*b = a1;
// }

// void	sort(char **array)
// {
// 	char	*tmp;
// 	int	i;
// 	int	j;

// 	j = 0;
// 	while (j < ft_array_size(array))
// 	{
// 		i = 0;
// 		while (i < ft_array_size(array))
// 		{
// 			if (array[i + 1] && ft_strcmp(array[i], array[i + 1]) > 0)
// 				ft_swap(&array[i], &array[i + 1]);
// 			i++;
// 		}
// 		j++;
// 	}
// }

// int run_export(char **args, t_envp *env)
// {
// 	int	i;
// 	char **dup_env;

// 	dup_env = env->tab;
// 	if (!args[1])
// 	{
// 		sort(dup_env);
// 		return (1);
// 	}
// 	i = 0;
// 	while (dup_env[i])
// 	{
// 		printf("%s\n", dup_env[i]);
// 		i++;
// 	}
// 	/////////////////////////
// 	/////////////////////////
// 	/////////////////////////
// 	return (1);
// }

// int main(int argc, char **argv)
// {
// 	run_export(argv);
// 	// sort(new_argv);
// 	// int i = 0;
// 	// while (new_argv[i])
// 	// {
// 	// 	printf("%s\n", new_argv[i]);
// 	// 	i++;
// 	// }
// 	// ft_free_array(new_argv, ft_array_size(new_argv));
// }