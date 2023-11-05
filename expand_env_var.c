/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarraffi <azarraffi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:14:29 by azarraffi         #+#    #+#             */
/*   Updated: 2023/11/05 11:36:55 by azarraffi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//FAIRE LA CONVERSION LST->TAB DE L'ENV DANS UNSET

//VOIR DANS BOUCLE WHILE DU MAIN DE BUILTIN_ENV : SI C'EST POSSIBLE D'ECRIRE SOUS FORME
//WHILE(ENV_TAB[i]) plutôt que WHILE(i < ...)

char *expand_env_var(char *token_value, char **env_tab)
{
    char *expanded_var;
    int     i;
    int     token_value_len;

    token_value_len = ft_strlen(token_value);
    i = 0;
    //est-ce que c'est possible d'écrire sous cette forme,
    // ou est-ce qu'il faut while (i < ...) ?
    while (env_tab[i])
    {
        if (ft_strncmp(env_tab[i], token_value, token_value_len))
            break;
        i++;
    }
    expanded_var = *(env_tab + i + 1); //????
    return (expanded_var);
}
