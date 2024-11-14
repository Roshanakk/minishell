/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:49:13 by balacam           #+#    #+#             */
/*   Updated: 2023/12/11 12:21:06 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sanitize_lst_tokens(t_token *head, t_general *general)
{
	if (merge_value_append(&head, general) == -2)
		return (EXIT_FAILURE);
	if (merge_value_redir(&head, general) == -2)
		return (EXIT_FAILURE);
	if (merge_value_heredoc(&head, general) == -2)
		return (EXIT_FAILURE);
	replace_word_value(&head, general);
	handle_quotes(general);
	return (0);
}
