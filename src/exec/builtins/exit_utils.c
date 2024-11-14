/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:09:21 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/06 12:34:55 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_error_true(bool *error)
{
	*error = true;
	return (0);
}

void	deal_with_minus_sign(int *n, int *i)
{
	*n = -(*n);
	(*i)++;
}
