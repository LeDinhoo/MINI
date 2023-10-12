/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:05:18 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 12:58:38 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

bool	is_builtin(t_cmd *current)
{
	if (!current->cmd_args)
		return (false);
	if (ft_strcmp(current->cmd_args[0], "cd") == 0
		|| ft_strcmp(current->cmd_args[0], "echo") == 0
		|| ft_strcmp(current->cmd_args[0], "pwd") == 0
		|| ft_strcmp(current->cmd_args[0], "export") == 0
		|| ft_strcmp(current->cmd_args[0], "unset") == 0
		|| ft_strcmp(current->cmd_args[0], "exit") == 0
		|| ft_strcmp(current->cmd_args[0], "env") == 0)
		return (true);
	else
		return (false);
}

int	env_build(t_mini *mini)
{
	print_env(mini->envp);
	return (0);
}

int	exec_bin(t_cmd *current, t_mini *mini)
{
	int	ret;

	ret = 0;
	if (!current->cmd_args)
		return (1);
	if (ft_strcmp(current->cmd_args[0], "unset") == 0)
		return (unset_build(current, mini));
	else if (ft_strcmp(current->cmd_args[0], "cd") == 0)
		return (cd_build(current, mini));
	else if (ft_strcmp(current->cmd_args[0], "env") == 0)
		return (env_build(mini));
	else if (ft_strcmp(current->cmd_args[0], "echo") == 0)
		return (echo_build(current));
	else if (ft_strcmp(current->cmd_args[0], "pwd") == 0)
		return (pwd_build());
	else if (ft_strcmp(current->cmd_args[0], "exit") == 0)
		return (exit_build(current, mini));
	else if (ft_strcmp(current->cmd_args[0], "export") == 0)
		return (export_build(mini));
	return (ret);
}

void	find_redirection(t_token *current, t_expect *ex)
{
	if (current->type == INPUT)
		ex->input = 1;
	else if (current->type == TRUNC)
		ex->output = 1;
	else if (current->type == APPEND)
		ex->append = 1;
	else if (current->type == HEREDOC)
		ex->heredoc = 1;
}
