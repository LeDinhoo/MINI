/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:08:29 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/05 16:51:00 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// FAIRE EN SORTE QUE "cd -" Marche;
// Phrase d'erreur a mettre a jour et a set pour PWD quand il n'existe;
// Clean les noms de fonctions
// Verifie bien ton code et peut etre rearrange tes fonctions pour que ce soit plus claire
// Analyser tes builtins trouver quelle differents retour d'erreur ils peuvent avoir;
// Ensuite connecte les retour d'erreurs (int) avec ret dans la fonction execbin();

#include "mini.h"

static char	*joning(char *result, char *s2, char *s1);
static char	*strjoin_bis(char const *s1, char const *s2);

char	*get_prompt_str(t_mini *mini)
{
	char		*user_home;
	char		*cwd;
	char		*directory;
	static char	prompt[PATH_MAX];

	sigaction(SIGINT, mini->sig->int_prompt, NULL);
	sigaction(SIGQUIT, mini->sig->quit_prompt, mini->sig->quit_exec);
	user_home = get_env("HOME", mini->envp);
	cwd = getcwd(NULL, 0);
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
	{
		return (ft_go_home(path, mini, old_pwd));
	}
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

bool	check_for_equal(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

char	**ft_add_to_env(t_mini *mini, char *str)
{
	char	**new_env;
	size_t	length_new_env;
	size_t	i;

	length_new_env = ft_lengh_array(mini->envp);
	new_env = ft_calloc(length_new_env + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	ft_memmove(new_env, mini->envp, length_new_env * sizeof(char *));
	free(mini->envp);
	return (new_env);
}

int	ft_update_env(t_mini *mini, char *old_pwd)
{
	char	*new_old_pwd;
	char	*new_pwd;
	char	*tmp;

	new_old_pwd = strjoin_bis("OLDPWD=", old_pwd);
	free(old_pwd);
	tmp = getcwd(NULL, 0);
	new_pwd = strjoin_bis("PWD=", tmp);
	free(tmp);
	if (ft_is_in_env(new_old_pwd, mini) == true)
		mini->envp = ft_add_to_env(mini, new_old_pwd);
	if (ft_is_in_env(new_pwd, mini) == true)
		mini->envp = ft_add_to_env(mini, new_pwd);
	free(new_old_pwd);
	free(new_pwd);
	return (0);
}

static char	*strjoin_bis(char const *s1, char const *s2)
{
	size_t	joined_size;
	char	*result;
	size_t	size_s1;
	size_t	size_s2;

	if (!s1 && !s2)
		return (NULL);
	if (!s2 && s1)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	joined_size = (size_s1 + size_s2);
	result = malloc(sizeof(char) * joined_size + 1);
	if (!result)
		return (NULL);
	return (joning(result, (char *)s2, (char *)s1));
}

static char	*joning(char *result, char *s2, char *s1)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (s1[x])
	{
		result[x] = s1[x];
		x++;
	}
	while (s2[y])
	{
		result[x] = s2[y];
		x++;
		y++;
	}
	result[x] = '\0';
	return (result);
}
