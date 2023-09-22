/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/21 19:44:05 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**init_myenvp(char **envp)
{
	char	**myenvp;
	int		len;
	
	len = 0;
	myenvp = NULL;
	if(!envp)
		return(NULL);
	while(envp[len])
		len++;
	myenvp = ft_calloc(len, sizeof(char *));
	if(!myenvp)
		return(NULL);
	len = 0;
	while (envp[len])
	{
		myenvp[len] = ft_strdup(envp[len]);
		len++;
	}
	return(myenvp);
}

void	init_struct(t_mini *mini, char **envp)
{
	mini->is_here_doc = 0;
	mini->input = NULL;
	mini->env = NULL;
	mini->start = NULL;
	mini->cmd_tab = NULL;
	mini->myenvp = NULL;
	mini->myenvp = init_myenvp(envp);
	mini->ret = SUCCESS;
	get_path(mini);
}

void	init_expect(t_expect *ex)
{
	ex->input = 0;
	ex->output = 0;
	ex->append = 0;
	ex->heredoc = 0;
}
