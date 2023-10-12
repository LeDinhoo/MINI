/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 18:24:46 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	add_var_to_shenv(t_mini *mini, char *str)
{
	int		len;
	char	**new_env;

	len = 0;
	while (mini->sh_envp && mini->sh_envp[len])
		len++;
	new_env = ft_calloc(len + 2, sizeof(char *));
	if (!new_env)
		return ;
	len = 0;
	while (mini->sh_envp && mini->sh_envp[len])
	{
		new_env[len] = ft_strdup(mini->sh_envp[len]);
		free(mini->sh_envp[len]);
		len++;
	}
	new_env[len] = ft_strdup(str);
	free(mini->sh_envp);
	mini->sh_envp = NULL;
	mini->sh_envp = new_env;
	return ;
}

void	modify_shvar_value(t_mini *mini, char *str, char *var_name)
{
	int		len;
	char	**new_env;

	len = 0;
	while (mini->sh_envp && mini->sh_envp[len])
		len++;
	new_env = ft_calloc(len + 1, sizeof(char *));
	if (!new_env)
		return ;
	len = 0;
	while (mini->sh_envp && mini->sh_envp[len])
	{
		if (ft_strncmp(mini->sh_envp[len], var_name, ft_strlen(var_name)) == 0)
			new_env[len] = ft_strdup(str);
		else
			new_env[len] = ft_strdup(mini->sh_envp[len]);
		free(mini->sh_envp[len]);
		len++;
	}
	free(mini->sh_envp);
	mini->sh_envp = NULL;
	mini->sh_envp = new_env;
	return ;
}

void	add_tmp_var(t_mini *mini, t_token *current)
{
	char	*var_name;

	var_name = find_var_name(current->str);
	if (ft_strlen(var_name) != 0 && is_in_export(var_name, mini->sh_envp) == 0)
	{
		if (ft_strchr(current->str, '=') != NULL)
			modify_shvar_value(mini, current->str, var_name);
	}
	else
		add_var_to_shenv(mini, current->str);
	if (ft_strlen(var_name) != 0 && is_in_export(var_name, mini->envp) == 0)
	{
		if (ft_strchr(current->str, '=') != NULL)
			modify_var_value(mini, current->str, var_name);
	}
	return ;
}

static void	set_command_type(t_token *current, int *redirection)
{
	if (!current->prev || current->prev->type == PIPE)
	{
		if (current->type == HEREDOC || current->type == INPUT
			|| current->type == APPEND || current->type == TRUNC)
			*redirection = 1;
		else if (current->type != EXPORT)
			current->type = CMD;
	}
}

void	update_token_types(t_mini *mini)
{
	t_token	*current;
	int		redirection;
	int		is_export;
	int		only_nine;

	is_export = 0;
	redirection = 0;
	only_nine = 0;
	export_and_only(mini, &is_export, &only_nine);
	current = mini->start;
	while (current != NULL)
	{
		if (is_here_doc(current))
			setup_here_doc(mini, current->next->str);
		if (current->next && redirection == 1)
		{
			current = current->next;
			if (current->type != EXPORT)
				current->type = CMD;
			redirection = 0;
		}
		set_command_type(current, &redirection);
		handle_exportable_type(current, only_nine, is_export, mini);
		current = current->next;
	}
}
