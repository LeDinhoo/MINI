/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:08:29 by hdupuy            #+#    #+#             */
/*   Updated: 2023/08/31 14:06:16 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_prompt_str(void)
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
	strcat(prompt, "\033[34mMiniShell\033[92m➜\033[0m \033[96m");
	strncat(prompt, directory, PATH_MAX - strlen(prompt) - 1);
	strcat(prompt, " \033[33m\033[0m");
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

void	cd_build(t_mini *mini)
{
	t_token *current;

	current = mini->start;
	if (current && current->str && strcmp(current->str, "cd") == 0)
	{
		if (current->next)
			minishell_cd(current->next->str);
		else
			minishell_cd("");
	}
}