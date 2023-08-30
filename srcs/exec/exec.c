/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:37:12 by hdupuy            #+#    #+#             */
/*   Updated: 2023/08/30 13:57:34 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void    cmd_args(t_mini* mini, int is_pipe)
{
    //Verifier si le premier token etant CMD est valide
        //Si Valide sauvegarder le path dans 
}

void	is_pipe(t_mini *mini)
{
	t_token	*current;
	int		is_pipe;

	is_pipe = 0;
	if (mini->start == NULL)
		return ;
	current = mini->start;
	while (current)
	{
		if (current->type == PIPE)
		{
			is_pipe = 1;
			// Variables pipe a 1 on est dans une ligne de commande pipe
		}
		current = current->next;
	}
	if (is_pipe == 1)
	{
		ft_printf("PIPE\n");
		// Lancer parsing pour plusieurs commandes
	}
	else
	{
		ft_printf("SOLO\n");
		// Donc une seul commande
		// Lancer le parsing pour une commande
        cmd_args(mini, is_pipe);
    }
    return ;
}

int	execution(t_mini *mini)
{
	is_pipe(mini);
	// char *const str_ls[3] = {"ls", "-zozio", NULL}; // Commande "ls -l"

	// // Exécution de la commande "ls -l"
	// if (fork() == 0)
	// {
	// 	execve("/usr/bin/ls", str_ls, NULL);
	// 	perror("execve ls");
	// 	exit(EXIT_FAILURE);
	// }

	// // Exécution de la commande inexistante "xyz123"
	// if (fork() == 0) {
	//     execve("/votre_chemin/xyz123", str_xyz, NULL);
	//     perror("execve xyz123");
	//     exit(EXIT_FAILURE);
	// }

	// // Attendre que les processus fils se terminent
	// wait(NULL);
	// wait(NULL);
	return (0);
}