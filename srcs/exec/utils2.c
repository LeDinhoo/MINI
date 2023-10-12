/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:02:20 by cbacquet          #+#    #+#             */
/*   Updated: 2023/10/12 18:26:17 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// Déclarations de fonctions auxiliaires
static char	*get_current_directory(t_mini *mini);
static void	build_prompt(char *prompt, char *directory, t_mini *mini);

char	*get_prompt_str(t_mini *mini)
{
	static char	prompt[PATH_MAX];
	char		*directory;

	sigaction(SIGINT, mini->sig->int_prompt, NULL);
	sigaction(SIGQUIT, mini->sig->quit_prompt, mini->sig->quit_exec);
	directory = get_current_directory(mini);
	ft_memset(prompt, 0, sizeof(prompt));
	build_prompt(prompt, directory, mini);
	return (prompt);
}

static char	*get_current_directory(t_mini *mini)
{
	char	*cwd;
	char	*user_home;
	char	*directory;

	user_home = get_env("HOME", mini->envp);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = "/UNKNOWN";
	if (user_home && ft_strcmp(cwd, user_home) == 0)
		directory = "~";
	else
	{
		directory = ft_strrchr(cwd, '/');
		if (directory == NULL)
			directory = "UNKNOWN";
		else
			directory++;
	}
	return (directory);
}

static void	build_prompt(char *prompt, char *directory, t_mini *mini)
{
	ft_strcat(prompt, "\033[34mMiniShell\033[92m ❯\033[0m \033[96m");
	ft_strcat(prompt, " ");
	ft_strncat(prompt, directory, PATH_MAX - ft_strlen(prompt) - 1);
	if (mini->ret == SUCCESS)
		ft_strcat(prompt, "\033[92m ❯\033[0m");
	else
		ft_strcat(prompt, "\033[31m ❯\033[0m");
	ft_strcat(prompt, "\033[33m\033[0m");
	ft_strcat(prompt, " ");
}

void	pipe_redirection(t_mini *mini, t_cmd *current, int pipe_fd[2], int i)
{
	if (i != 0)
	{
		if (mini->input_fd != 0)
		{
			dup2(mini->input_fd, STDIN_FILENO);
			close(mini->input_fd);
		}
	}
	if (current->cmd && current->is_last == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}
