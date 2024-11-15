/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:04:52 by azarraffi         #+#    #+#             */
/*   Updated: 2023/12/06 12:34:33 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	can_be_unset(char *var, char *node_content)
{
	size_t	var_len;

	var_len = ft_strlen(var);
	if ((var_len == len_until_equal_sign(node_content))
		&& !ft_strncmp(node_content, var, var_len))
		return (1);
	return (0);
}

void	remove_from_env(char *var, t_list **env_lst)
{
	t_list	*node;
	t_list	*previous;

	node = *env_lst;
	if (can_be_unset(var, node->content))
	{
		*env_lst = node->next;
		ft_lstdelone(node);
		return ;
	}
	node = (*env_lst)->next;
	previous = *env_lst;
	while (node)
	{
		if (can_be_unset(var, node->content))
		{
			previous->next = node->next;
			ft_lstdelone(node);
			break ;
		}
		node = node->next;
		previous = previous->next;
	}
}

int	run_unset(char **cmd, t_general *general)
{
	int	i;

	if (!cmd[1])
		return (EXIT_SUCCESS);
	i = ft_array_size(cmd) - 1;
	while (i)
	{
		if (!check_valid_identifier(cmd[i]))
		{
			print_error("minishell", "unset", cmd[i], "not a valid identifier");
			return (EXIT_FAILURE);
		}
		else
			remove_from_env(cmd[i], &general->env_lst);
		i--;
	}
	return (convert_env_to_tab(general));
}

// int	run_unset(char **args, t_envp *env)
// {
// 	int	i;

// 	if (!args[1])
// 		return (EXIT_SUCCESS);
// 	i = ft_array_size(args) - 1;
// 	while (i)
// 	{
// 		if (!check_valid_identifier(args[i]))
//         {
// 			ft_putstr_fd("minishell: unset: `", 1);
// 			ft_putstr_fd(args[i], 1);
// 			ft_putstr_fd("`: not a valid identifier\n", 1);
// 		}
// 		else
// 			remove_from_env(args[i], &env->lst);
// 		i--;
// 	}
// 	return (EXIT_SUCCESS);
// }

// int main(int argc, char **argv, char **envp)
// {
//  	t_list *first_node = ft_lstnew(ft_strdup("ROXANE=bonjour"));
// 	t_list *tmp ;
// 	t_list *tmp2 ;

// 	ft_lstadd_back(&first_node, ft_lstnew(ft_strdup("HELLO=quoi")));
// 	ft_lstadd_back(&first_node, ft_lstnew(ft_strdup("VAR3=hey")));
// 	ft_lstadd_back(&first_node, ft_lstnew(ft_strdup("VAR4=hey")));

// 	// remove_from_env("HELLO", &first_node);
// 	// t_general general;

// 	// if (create_env_lst(envp, &general))
// 	// 	return (EXIT_FAILURE);
// 	// if (convert_env_to_tab(&general))
// 	// 	return (ft_lstclear(&(first_node)), EXIT_FAILURE);

// 	remove_from_env("HELLO=quoi", &first_node);
// 	tmp = first_node;
// 	while (tmp)
// 	{
// 		printf("%s\n", tmp->content);
// 		tmp = tmp->next;
// 	}
// 	ft_lstclear(&first_node);
// 	// ft_free_array(env.tab, ft_array_size(env.tab));
// }