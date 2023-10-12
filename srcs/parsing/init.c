/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 18:49:25 by hdupuy           ###   ########.fr       */
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
	int		i;
	char	*nbshlvl;

	if (!get_env("PWD", mini->envp))
	{
		new_var = ft_strdup("PWD=");
		new_var = ft_strjoin(new_var, getcwd(NULL, 0));
		add_var_to_env(mini, new_var);
	}
	if (get_env("SHLVL", mini->envp))
	{
		nbshlvl = getenv("SHLVL");
		ft_printf("%s\n", nbshlvl);
		new_var = ft_strdup("SHLVL=");
		new_var = ft_strjoin(new_var, ft_itoa(i));
		modify_var_value(mini, new_var, "SHLVL");
	}
	else if (!get_env("SHLVL", mini->envp))
	{
		new_var = ft_strdup("SHLVL=1");
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
