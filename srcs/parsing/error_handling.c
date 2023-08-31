/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:21:21 by hdupuy            #+#    #+#             */
/*   Updated: 2023/08/31 16:18:32 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_error(char *action)
{
	ft_printf("mini: ");
	ft_printf("%s\n", action);
}

char	*pipe_prompt(void)
{
	static char	prompt[PATH_MAX];

	memset(prompt, 0, sizeof(prompt));
	strcat(prompt, "pipe> ");
	return (prompt);
}

int	pars_error(t_mini *mini)
{
	t_token *current;
	char *prompt;

	current = mini->start;
	while (current != NULL)
	{
		if (!current->next && (current->type == TRUNC || current->type == APPEND
				|| current->type == INPUT || current->type == HEREDOC))
		{
			print_error(LINE_ERR);
			return (0);
		}
		if (!current->prev && current->type == PIPE)
		{
			print_error(PIPE_ERR);
			return (0);
		}
		if (current->next && current->prev)
		{
			if ((current->prev->type == PIPE || current->next->type == PIPE)
				&& current->type == PIPE)
			{
				print_error(PIPE_ERR);
				return (0);
			}
		}
		if (!current->next && current->type == PIPE)
		{
			prompt = pipe_prompt();
			mini->input = readline(prompt);
			mini->start = split_string(mini->input, mini);
			if (!pars_error(mini))
				return (0);
		}
		current = current->next;
	}
	return (1);
}