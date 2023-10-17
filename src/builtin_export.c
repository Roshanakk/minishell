/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:04:58 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/17 11:58:00 by rraffi-k         ###   ########.fr       */
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
		if (ft_strcmp(tmp->content, var_and_value))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_to_env(t_envp *env, char *var_and_value)
{
	int	i;
	t_list *var_exists;
	var_exists = var_node_exists(env->lst, var_and_value);
	i = 0;
	//si la var n'est pas deja dans l'env
		//on lst_addback dans la liste chainee
	//sinon
		//si concatenate
			//on strjoin la partie apres le '='
		//sinon
			//on free et set a NULL la var
			//on met la nouvelle valeur
	//free env->tab et reappeler conv_env_to_tab ?
}


/* arg[0] = "export" ; je recois les var d'env sans les guillemets */
int run_export(char **args, t_envp *env)
{
	int	i;
	
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
		i++;
		// add_to_env(env, args[i]);
	}
	return (1);
}

int main(int argc, char **argv, char **env)
{
	printf("%d\n", check_valid_identifier(argv[1]));
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