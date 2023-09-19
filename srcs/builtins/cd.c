/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:08:29 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/19 11:28:06 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_prompt_str(t_mini *mini)
{
	char		*user_home;
	char		*cwd;
	char		*directory;
	static char	prompt[PATH_MAX];

	user_home = getenv("HOME");
	cwd = getenv("PWD");
	if (!cwd)
		cwd = "/UNKNOWN";
	if (user_home && strcmp(cwd, user_home) == 0)
		directory = "~";
	else
	{
		directory = strrchr(cwd, '/');
		if (directory == NULL)
			directory = "UNKNOWN";
		else
			directory++;
	}
	memset(prompt, 0, sizeof(prompt));
	strcat(prompt, "\033[90m╭─\033[0m");
	strcat(prompt, "\033[34mMiniShell\033[92m ❯\033[0m \033[96m");
	strcat(prompt, " ");
	strncat(prompt, directory, PATH_MAX - strlen(prompt) - 1);
	strcat(prompt, " \033[90m\n╰─\033[0m");
	if (mini->ret == SUCCESS)
		strcat(prompt, "\033[92m❯\033[0m");
	else
		strcat(prompt, "\033[31m❯\033[0m");
	strcat(prompt, "\033[33m\033[0m");
	strcat(prompt, " ");
	return (prompt);
}

int	minishell_cd(char *path)
{
	char	*home;
	char	*cwd;

	if (path == NULL || strcmp(path, "") == 0)
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			fprintf(stderr, "minishell: HOME environment variable not set\n");
			return (-1);
		}
		path = home;
	}
	if (chdir(path) != 0)
	{
		perror("minishell");
		return (-1);
	}
	cwd = malloc(PATH_MAX);
	if (cwd == NULL)
	{
		perror("malloc");
		return (-1);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("minishell");
		free(cwd);
		return (-1);
	}
	if (setenv("PWD", cwd, 1) != 0)
	{
		perror("minishell");
		free(cwd);
		return (-1);
	}
	free(cwd);
	return (0);
}

void	cd_build(t_cmd *cmd)
{
	char	*path;
	char	*old_pwd;

	path = NULL;
	if (cmd->cmd_args[1] && cmd->cmd_args[2])
	{
		write(1, "minishell : cd : too many argmuents\n", 19);
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (cmd->cmd_args[0] && cmd->cmd_args[1] == NULL)
		return (ft_go_home(cmd, path, old_pwd));
	else if (cmd->cmd_args[1][0] == '-' && cmd->cmd_args[1][1] == '\0')
	{
		ft_go_back_path(cmd, path, old_pwd);
		return ;	
	}
	 
	if (cmd->cmd_args[0] && cmd->cmd_args[1])
	{
		ft_update_env(cmd, path);
	}
	
	/*if (current && current->str && strcmp(current->str, "cd") == 0)
	{
		if (current->next)
			minishell_cd(current->next->str);
		else
			minishell_cd("");
	}*/
}

void	ft_go_home(t_cmd *cmd, char *path, char *old_pwd)
{
	char *tmp_path;
	char *home;

	tmp_path = getenv("PWD");
	home = getenv("HOME");
	
}

void	ft_go_back_path(t_cmd *cmd, char *path, char *old_pwd)
{
	char *old_path;
	
	old_path = getenv("PWD");
	path = getenv("OLDPWD");
}

void	ft_update_env(t_cmd * cmd, char *path)
{
	
}
