/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:04:52 by azarraffi         #+#    #+#             */
/*   Updated: 2023/10/20 15:19:41 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	remove_from_env(char *var_and_value, t_list **env_lst)
{
	t_list *node;
	t_list *previous;
	size_t len;

	node = *env_lst;
	len = len_until_equal_sign(var_and_value);
	if ((len == len_until_equal_sign(node->content))
		&& !ft_strncmp(node->content, var_and_value, len))
	{
		*env_lst = node->next;
		ft_lstdelone(node);
		return ;
	}
	node = (*env_lst)->next;
	previous = *env_lst;
	while (node && !(len == len_until_equal_sign(node->content))
			&& ft_strncmp(node->content, var_and_value, len))
	{
		previous = previous->next;
		node = node->next;
	}
	if (!node)
		return ;
	previous->next = node->next;
	ft_lstdelone(node);
}


int	run_unset(char **args, t_envp *env)
{
	int	i;

	if (!args[1])
		return (EXIT_SUCCESS);
	i = ft_array_size(args) - 1;
	while (i)
	{
		if (!check_valid_identifier(args[i]))
        {
			ft_putstr_fd("minishell: unset: `", 1);
			ft_putstr_fd(args[i], 1);
			ft_putstr_fd("`: not a valid identifier\n", 1);
		}
		else
			remove_from_env(args[i], &env->lst);
		i--;
	}
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
 	t_list *first_node = ft_lstnew(ft_strdup("ROXANE=bonjour"));
	t_list *tmp ;
	t_list *tmp2 ;

	ft_lstadd_back(&first_node, ft_lstnew(ft_strdup("HELLO=quoi")));
	ft_lstadd_back(&first_node, ft_lstnew(ft_strdup("VAR3=hey")));
	ft_lstadd_back(&first_node, ft_lstnew(ft_strdup("VAR4=hey")));

	// remove_from_env("HELLO", &first_node);
	remove_from_env("ROXANE=bonjour", &first_node);
	tmp = first_node;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&first_node);
}