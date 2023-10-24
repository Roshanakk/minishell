/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_call_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:31:10 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/24 14:59:32 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	convert_token_lst_to_tab(t_token *cmdline)
{
    
}




int main(int argc, char**argv, char **envp)
{
    char test[] = "echo -n bonjour ca va | grep bonjour > outfile1 > outfile2 > outfile3";

    // on split les PIPE, REDIR_INPUT, REDIR_OUTPUT
    //on cree un char ** de commandes avec les redirs pour chaque commande
    //s'il y a un >, on met la redir dans la cmd precedente
    //s'il y a un <, on met la redir dans la cmd suivante
    //si plusieurs redirs
    //si 
    /*
    while token
        if type == REDIR_INPUT || type == REDIR_OUTPUT || type == PIPE
    
    */
}
