/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:05:18 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/06 15:47:00 by hdupuy           ###   ########.fr       */
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

void	env_build(t_mini *mini)
{
	print_env(mini->envp);
}

void	exec_bin(t_cmd *current, t_mini *mini)
{
	int	ret;

	ret = 0;
	// toute les builtin doivent avoir cette norm : ret = unset_build(current,
		// mini);
	if (!current->cmd_args)
		return ;
	if (ft_strcmp(current->cmd_args[0], "unset") == 0)
		unset_build(current, mini);
	else if (ft_strcmp(current->cmd_args[0], "cd") == 0)
		return (cd_build(current, mini));
	else if (ft_strcmp(current->cmd_args[0], "env") == 0)
		env_build(mini);
	else if (ft_strcmp(current->cmd_args[0], "echo") == 0)
		echo_build(current);
	// else if (ft_strcmp(current->cmd_args[0], "export") == 0)
	// 	export_build(current, mini);
	return ;
	// return (ret);
}
