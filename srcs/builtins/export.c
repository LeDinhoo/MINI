/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:30:30 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/06 14:04:51 by hdupuy           ###   ########.fr       */
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
	var_name = ft_calloc(i - 1, sizeof(char));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = '\0';
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
}

int	export_build(t_cmd *current, t_mini *mini)
{
	t_token *cur_tkn;
	char *var_name;

	cur_tkn = mini->start;
	while (cur_tkn)
	{
		if (cur_tkn->type == EXPORT)
		{
			var_name = find_var_name(cur_tkn->str);
			ft_printf("%s\n", var_name);
			if (get_env(var_name, mini->envp) == NULL)
				add_var_to_env(mini, cur_tkn->str);
			else
				modify_var_value(mini, cur_tkn->str, var_name);
		}
		else if (get_env(cur_tkn->str, mini->sh_envp))
		{
			var_name = get_var_str(mini->sh_envp, cur_tkn->str);
			if (get_env(cur_tkn->str, mini->envp) == NULL)
				add_var_to_env(mini, var_name);
			else
				modify_var_value(mini, var_name, cur_tkn->str);
		}
		cur_tkn = cur_tkn->next;
	}
	return (0);
}