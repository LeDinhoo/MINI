/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/06 16:03:50 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**init_myenvp(char **envp)
{
	char	**myenvp;
	int		len;

	len = 0;
	myenvp = NULL;
	if (!envp)
		return (NULL);
	while (envp[len])
		len++;
	myenvp = ft_calloc(len + 1, sizeof(char *));
	if (!myenvp)
		return (NULL);
	len = 0;
	while (envp[len])
	{
		myenvp[len] = ft_strdup(envp[len]);
		len++;
	}
	return (myenvp);
}

void	setup_findable_var(t_mini *mini)
{
	char	*new_var;

	if (!get_env("PWD", mini->envp))
	{
		new_var = ft_strdup("PWD=");
		new_var = ft_strjoin(new_var, getcwd(NULL, 0));
		add_var_to_env(mini, new_var);
	}
}

void	init_struct(t_mini *mini, char **envp)
{
	mini->is_here_doc = 0;
	mini->input = NULL;
	mini->path = NULL;
	mini->start = NULL;
	mini->cmd_tab = NULL;
	mini->envp = NULL;
	mini->envp = init_myenvp(envp);
	setup_findable_var(mini);
	mini->ret = SUCCESS;
	mini->savein = dup(0);
	mini->saveout = dup(1);
	mini->saveerr = dup(2);
	mini->sh_envp = NULL;
	get_path(mini);
}

void	init_expect(t_expect *ex)
{
	ex->input = 0;
	ex->output = 0;
	ex->append = 0;
	ex->heredoc = 0;
}
