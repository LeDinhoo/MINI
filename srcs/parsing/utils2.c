/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:29:04 by cbacquet          #+#    #+#             */
/*   Updated: 2023/10/10 22:13:55 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	is_cmd(t_token *current, char **env, int i)
{
	char	*cmd;
	char	*path;

	while (env[i])
	{
		cmd = current->str;
		path = ft_strdup(env[i]);
		path = ft_strjoin(path, "/");
		cmd = ft_strjoin(path, cmd);
		if (access(cmd, F_OK | X_OK) == 0)
			current->type = CMD;
		i++;
		free(cmd);
	}
}

char	*get_env(const char *name, char **myenvp)
{
	int		i;
	char	*env_entry;

	i = 0;
	if (!myenvp || !name)
		return (NULL);
	while (myenvp[i])
	{
		env_entry = myenvp[i];
		if (ft_strncmp(env_entry, name, strlen(name)) == 0
			&& env_entry[ft_strlen(name)] == '=')
			return (env_entry + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}

char	*substitute_variable_value(char *token, t_split *tkn)
{
	t_switch	swap;
	int			dollarpos;

	swap.is_switch = 0;
	swap.substitutedtoken = token;
	while (ft_strchr(swap.substitutedtoken, '$') != NULL
		&& tkn->in_simple_quotes == 0)
	{
		swap.variablename = find_dollar_value(swap.substitutedtoken,
				ft_strichr(swap.substitutedtoken, '$'));
		if (ft_strcmp(swap.variablename, "$?") == 0)
			handle_last_return_value(&swap, tkn);
		else
			handle_classic_env_value(&swap, tkn);
		free(swap.variablename);
		dollarpos = ft_strichr(swap.substitutedtoken, '$');
		if (swap.substitutedtoken[dollarpos + 1] == '\0')
			break ;
	}
	if (swap.is_switch == 0)
		swap.substitutedtoken = strdup(token);
	if (!swap.substitutedtoken)
		return (NULL);
	return (swap.substitutedtoken);
}
