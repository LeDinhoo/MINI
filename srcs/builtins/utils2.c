/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:55:40 by cbacquet          #+#    #+#             */
/*   Updated: 2023/10/12 20:11:47 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*joning(char *result, char *s2, char *s1);

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

char	**ft_add_to_env(t_mini *mini)
{
	char	**new_env;
	size_t	length_new_env;

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
		mini->envp = ft_add_to_env(mini);
	if (ft_is_in_env(new_pwd, mini) == true)
		mini->envp = ft_add_to_env(mini);
	free(new_old_pwd);
	free(new_pwd);
	return (0);
}

char	*strjoin_bis(char const *s1, char const *s2)
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

char	*joning(char *result, char *s2, char *s1)
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
