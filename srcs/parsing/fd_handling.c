/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:27:11 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/04 09:15:30 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


//Ajoute le here_doc FD a la commande
void	setup_here_doc(t_mini *mini, char *limiter)
{
    char    *s1;
    char    *prompt;

	mini->is_here_doc = 1;
	mini->here_doc_fd = open("/tmp/.pipex_here_doc",
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (mini->here_doc_fd < 0)
		ft_printf("ERROR");
	while (1)
	{
		prompt = here_prompt();
		s1 = readline(prompt);
		if (ft_strncmp(s1, limiter, ft_strlen(limiter)) == 0)
		{
			free(s1);
			break ;
		}
		ft_putstr_fd(s1, mini->here_doc_fd);
		ft_putstr_fd("\n", mini->here_doc_fd);
		free(s1);
	}
	close(mini->here_doc_fd);
}