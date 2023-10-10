/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:07:29 by clement           #+#    #+#             */
/*   Updated: 2023/10/09 18:03:24 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	exit_build(t_cmd *current, t_mini *mini)
{
	int		ret_val;
	bool	is_error;

	is_error = false;
	ret_val = get_return_value(current->cmd_args, &is_error, mini);
	if (ret_val == 1 && is_error)
	{
		printf("exit \n Minishell: exit: too many arguments\n");
		return (1);
	}
	free_env(mini);
	if (ret_val == 2 && is_error)
		printf("Minishell: exit: required numerical argument\n");
	mini->ret = ret_val;
	exit(ret_val);
}

int	get_return_value(char **argv, bool *is_error, t_mini *mini)
{
	int	i;

	printf("exit\n");
	if (!argv[1])
		return (mini->ret);
	else if (argv[1] && argv[2])
		return (*is_error = true, 1);
	else
	{
		i = 0;
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
				return (*is_error = true, 2);
			i++;
		}
		return (ft_atoi(argv[1]));
	}
}
