/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:24:19 by balacam           #+#    #+#             */
/*   Updated: 2023/12/09 16:58:09 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenization(t_general *general, char *str)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = DEFAULT;
	while (++i <= end)
	{
		status = set_status(status, str, i);
		if (status == DEFAULT)
			start = save_word_or_sep(&i, str, start, general);
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			printf("unexpected EOF while looking for matching\n");
		else if (status == SQUOTE)
			printf("unexpected EOF while looking for matching\n");
		printf("unexpected end of file\n");
		return (1);
	}
	return (0);
}
