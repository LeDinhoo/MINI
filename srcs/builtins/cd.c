/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:08:29 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/22 12:28:22 by clement          ###   ########.fr       */
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

/*int	minishell_cd(char *path)
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
}*/

void	cd_build(t_cmd *cmd, t_mini *mini)
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
		return (ft_go_home(path, mini, old_pwd));
	else if (cmd->cmd_args[1][0] == '-' && cmd->cmd_args[1][1] == '\0')
	{
		ft_go_old_pwd(path, mini, old_pwd);
		return ;	
	}
	if (cmd->cmd_args[0] && cmd->cmd_args[1])
		ft_update_env(mini, old_pwd);	
}
	/*if (current && current->str && strcmp(current->str, "cd") == 0)
	{
		if (current->next)
			minishell_cd(current->next->str);
		else
			minishell_cd("");
	}*/

void	ft_go_home(char *path, t_mini *mini, char *old_pwd)
{
	path = getenv("HOME");
	if (path == NULL)
		return (printf("Home not set\n"), (void) 0);
	if (chdir(&path[5]) == -1)
		return (printf("cd: %s: No such file or directory\n", path), (void) 0);
	return (ft_update_env(mini, old_pwd), (void) 0);
}

void	ft_go_old_pwd(char *path, t_mini *mini, char *old_pwd)
{	
	path = getenv("OLDPWD");
	if (path == NULL)
		return (printf("cd : OLDPWD not set"), (void) 0);
	if (chdir(&path[7]) == - 1)
		return (printf("cd : %s: No such file or directory\n", path), (void) 0);
	return (ft_update_env(mini, old_pwd));
}

bool ft_is_in_env(char *str, t_mini *mini)
{
	int i;
	char **cpy_envp;
	int	len_str;
	
	i = 0;
	cpy_envp = mini->myenvp;
	len_str = ft_strlen(str);
	if(!str || !mini || !mini->myenvp)
		return (false);
	while (cpy_envp[i])
	{
		if (ft_strnstr(str, cpy_envp[i], len_str) != 0)
			return (true);
		i++;
	}
	return (false);
}


char **ft_add_to_env(t_mini *mini, char *str)
{
	//char	**old_env;
	char	**new_env;
	size_t	length_new_env;
	//size_t	i;
	//size_t	j;
	
	length_new_env = ft_lengh_array((void **)mini->myenvp);
	//i = ft_lengh_array((void **)old_env);
	new_env = ft_calloc(length_new_env + 2, sizeof( char *));
	if (!new_env)
		return (NULL);
	ft_memmove(new_env, mini->myenvp, length_new_env * (sizeof(char *)));
	new_env[length_new_env] = ft_strdup(str);
	free(mini->myenvp);
	return(new_env);
	/*j = 0;
	while (j < i)
	{
		new_env[j] = ft_strdup(old_env[j]);
		j++;
	}
	new_env[i] = ft_strdup(str);
	ft_free_array(old_env);
	return(new_env);*/
}

void	ft_update_env(t_mini *mini, char *old_pwd)
{
	char	*new_old_pwd;
	char	*new_pwd;
	char	*tmp;

	new_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	tmp = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (!ft_is_in_env(new_pwd, mini))
		mini->myenvp = ft_add_to_env(mini, new_pwd);
	if (!ft_is_in_env(old_pwd, mini))
		mini->myenvp = ft_add_to_env(mini, old_pwd);
	free(new_old_pwd);
	free(old_pwd);
}
