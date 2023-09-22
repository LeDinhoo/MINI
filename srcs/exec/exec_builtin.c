/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:05:18 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/21 20:08:09 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*int	builtin_exec(t_cmd *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd->cmd_args[0], "cd") == 0)
	{
		cd_build(cmd);
		return(1);
	}
	if (ft_strcmp(cmd->cmd_args[0], "echo") == 0)
		echo_build(cmd);
	if (ft_strcmp(cmd->cmd_args[0], "export") == 0)
		export_build(cmd);
	if (ft_strcmp(cmd->cmd_args[0], "pwd") == 0)
		pwd_build(cmd);
	if (ft_strcmp(cmd->cmd_args[0], "unset") == 0)
		unset_build(cmd);
	if (ft_strcmp(cmd->cmd_args[0], "exit") == 0)
		exit_build(cmd);
	if (ft_strcmp(cmd->cmd_args[0], "env") == 0)
		env_build(cmd);
}*/
void	builtin_exec(t_mini *mini)
{
	t_token	*current;

	if (mini->start == NULL)
		return ;
	current = mini->start;
	if (ft_strcmp(current->str, "cd") == 0)
		cd_build(mini->cmd_tab, mini);
	if (ft_strcmp(current->str, "echo") == 0)
		echo_build(mini->start);
}