/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:43:30 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/10 20:33:22 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	envp = NULL;
}

char	**init_new_envp(char **myenvp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (myenvp[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	return (new_env);
}

int	unset_build(t_cmd *current, t_mini *mini)
{
	char	**new_env;
	int		i;
	int		j;
	int		arg;

	new_env = init_new_envp(mini->envp);
	i = 0;
	j = 0;
	arg = 1;
	while (mini->envp[j])
	{
		while (current->cmd_args[arg])
			if (!ft_strstr(mini->envp[j], current->cmd_args[arg++]))
				new_env[i++] = ft_strdup(mini->envp[j]);
		j++;
		arg = 1;
	}
	free_envp(mini->envp);
	mini->envp = new_env;
	return (0);
}

/*int	unset_build(t_cmd *current, t_mini *mini)
{
	char	**new_env;
	int		i;
	int		j;
	int		arg;

	new_env = NULL;
	new_env = init_new_envp(mini->envp);
	i = 0;
	j = 0;
	arg = 1;
	while (mini->envp[j])
	{
		while (current->cmd_args[arg])
		{
			if (ft_strstr(mini->envp[j], current->cmd_args[arg]))
			{
				j++;
				arg = 0;
			}
			arg++;
		}
		new_env[i] = ft_strdup(mini->envp[j]);
		i++;
		j++;
		arg = 1;
	}
	free_envp(mini->envp);
	mini->envp = new_env;
	return (0);
}*/
