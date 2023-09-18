/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 14:02:23 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_list(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		if (current->prev)
			printf("Token: %s, Type: %d\n", current->str, current->type);
		else
			printf("Token: %s, Type: %d\n", current->str, current->type);
		current = current->next;
	}
}

void	print_args(t_mini *mini)
{
	int		i;
	t_cmd	*current;

	i = 0;
	if (mini->cmd_tab == NULL)
		return ;
	current = mini->cmd_tab;
	while (current != NULL)
	{
		ft_printf("---- Command ----\ncmd : %s\n", current->cmd);
		ft_printf("path : %s\n", current->cmd_path);
		while (current->cmd_args && current->cmd_args[i])
		{
			ft_printf("args : %s\n", current->cmd_args[i]);
			i++;
		}
		ft_printf("--- Redirection ---\noutput : %s\n",
			current->redir.output_file);
		ft_printf("append : %s\n", current->redir.append_file);
		ft_printf("input : %s\n", current->redir.input_file);
		ft_printf("heredoc : %s\n\n", current->redir.heredoc_content);
		current = current->next;
		i = 0;
	}
}

void	print_error(char *action)
{
	ft_printf("mini: ");
	ft_printf("%s\n", action);
}
