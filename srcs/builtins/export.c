/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:30:30 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 15:54:45 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*find_var_name(char *str)
{
	char	*var_name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		var_name[i] = str[i];
		i++;
	}
	return (var_name);
}

void	add_var_to_env(t_mini *mini, char *str)
{
	int		len;
	char	**new_env;

	len = 0;
	while (mini->envp[len])
		len++;
	new_env = ft_calloc(len + 2, sizeof(char *));
	if (!new_env)
		return ;
	len = 0;
	while (mini->envp[len])
	{
		new_env[len] = ft_strdup(mini->envp[len]);
		free(mini->envp[len]);
		len++;
	}
	new_env[len] = ft_strdup(str);
	free(mini->envp);
	mini->envp = NULL;
	mini->envp = new_env;
	return ;
}

void	modify_var_value(t_mini *mini, char *str, char *var_name)
{
	int		len;
	char	**new_env;

	len = 0;
	while (mini->envp[len])
		len++;
	new_env = ft_calloc(len + 1, sizeof(char *));
	if (!new_env)
		return ;
	len = 0;
	while (mini->envp[len])
	{
		if (ft_strncmp(mini->envp[len], var_name, ft_strlen(var_name)) == 0)
			new_env[len] = ft_strdup(str);
		else
			new_env[len] = ft_strdup(mini->envp[len]);
		free(mini->envp[len]);
		len++;
	}
	free(mini->envp);
	mini->envp = NULL;
	mini->envp = new_env;
	return ;
}

char	*get_var_str(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}
