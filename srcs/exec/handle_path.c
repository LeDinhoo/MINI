/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:29:53 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/19 10:18:47 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	not_found(char *str)
{
	ft_printf("mini: ");
	ft_printf("%s: command not found\n", str);
}

void	absolute_not_found(char *str)
{
	ft_printf("mini: No such file or directory: ");
	ft_printf("%s\n", str);
}

int	handle_absolute_path(t_cmd *node, char *str)
{
	if (access(str, F_OK | X_OK) == 0)
	{
		node->cmd_path = ft_strdup(str);
		return (1);
	}
	return (0);
}

int	access_path(char **env, t_cmd *node, char *str)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	if (env == NULL || !str[0])
		return (0);
	while (env[i])
	{
		tmp = str;
		path = ft_strdup(env[i]);
		path = ft_strjoin(path, "/");
		tmp = ft_strjoin(path, tmp);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			node->cmd_path = ft_strdup(tmp);
			free(tmp);
			return (1);
		}
		i++;
		free(tmp);
	}
	return (0);
}

int	handle_path(char **env, t_cmd *node, char *str)
{
	if (str[0] == '/' || (str[0] == '.' && str[1] == '/'))
	{
		if (handle_absolute_path(node, str))
			return (1);
		else
			return (0);
	}
	if (access_path(env, node, str))
		return (1);
	else
		return (0);
}
