/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:08:29 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/02 12:56:04 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_prompt_str(t_mini *mini)
{
	char		*user_home;
	char		*cwd;
	char		*directory;
	static char	prompt[PATH_MAX];

	user_home = get_env("HOME", mini->envp);
	cwd = get_env("PWD", mini->envp);
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

int	minishell_cd(char *path, t_mini *mini)
{
	char	*home;
	char	*cwd;

	if (path == NULL || strcmp(path, "") == 0)
	{
		home = get_env("HOME", mini->envp);
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

void	cd_build(t_mini *mini)
{
	t_token	*current;

	current = mini->start;
	if (current && current->str && strcmp(current->str, "cd") == 0)
	{
		if (current->next)
			minishell_cd(current->next->str, mini);
		else
			minishell_cd("", mini);
	}
}
