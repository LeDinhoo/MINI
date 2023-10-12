/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:08:29 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/10 20:08:37 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	cd_build(t_cmd *current, t_mini *mini)
{
	char	*path;
	char	*old_pwd;
	int		i;

	path = NULL;
	i = 0;
	while (current->cmd_args[i])
		i++;
	if (i > 2)
	{
		write(1, "minishell : cd : too many argmuents\n", 37);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (!current->cmd_args[1])
		return (ft_go_home(path, mini, old_pwd));
	else if (current->cmd_args[1][0] == '-' && current->cmd_args[1][1] == '\0')
		return (ft_go_old_pwd(path, mini, old_pwd));
	else
		path = current->cmd_args[1];
	if (chdir(path) == -1)
		return (dprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno)),
			1);
	return (ft_update_env(mini, old_pwd));
}

int	ft_go_home(char *path, t_mini *mini, char *old_pwd)
{
	path = get_env("HOME", mini->envp);
	if (path == NULL)
	{
		printf("mini: cd: « HOME » not set\n");
		return (1);
	}
	if (chdir(path) == -1)
	{
		return (printf("cd: %s: No such file or directory\n", path), 1);
	}
	return (ft_update_env(mini, old_pwd));
}

int	ft_go_old_pwd(char *path, t_mini *mini, char *old_pwd)
{
	path = get_env("OLDPWD", mini->envp);
	if (path == NULL)
		return (printf("mini: cd: OLDPWD not set\n"), 1);
	if (chdir(path) == -1)
		return (printf("cd : %s: No such file or directory\n", path), 1);
	return (ft_update_env(mini, old_pwd));
}

bool	ft_is_in_env(char *str, t_mini *mini)
{
	int		i;
	int		len_until_equal;
	bool	have_equal;

	have_equal = check_for_equal(str);
	if (!have_equal)
		return (only_key_already_in_env(str, mini));
	i = 0;
	len_until_equal = 0;
	while (str[len_until_equal] && str[len_until_equal] != '=')
		len_until_equal++;
	while (mini->envp[i])
	{
		if (ft_strncmp(str, mini->envp[i], len_until_equal) == 0)
		{
			free(mini->envp[i]);
			mini->envp[i] = ft_strdup(str);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	only_key_already_in_env(char *str, t_mini *mini)
{
	size_t	key_len;
	int		i;

	key_len = ft_strlen(str);
	i = -1;
	while (mini->envp[++i])
	{
		if (ft_strncmp(str, mini->envp[i], key_len) == 0)
			return (true);
	}
	return (false);
}
