/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:05:18 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/19 11:40:50 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	builtin_exec(t_cmd *cmd)
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
}
