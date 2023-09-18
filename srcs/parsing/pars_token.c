/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:40:34 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 14:22:53 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*pipe_prompt(void)
{
	static char	prompt[PATH_MAX];

	memset(prompt, 0, sizeof(prompt));
	strcat(prompt, "pipe> ");
	return (prompt);
}

char	*here_prompt(void)
{
	static char	here_prompt[PATH_MAX];

	memset(here_prompt, 0, sizeof(here_prompt));
	strcat(here_prompt, "heredoc> ");
	return (here_prompt);
}

int	missing_pipe(t_mini *mini, t_token *current)
{
	char	*prompt;

	if (!current->next && current->type == PIPE)
	{
		prompt = pipe_prompt();
		mini->input = readline(prompt);
		mini->start = split_string(mini->input, mini);
		if (!pars_token(mini))
			return (0);
	}
	return (1);
}

int	is_here_doc(t_token *current)
{
	if (current->type == HEREDOC)
		return (1);
	return (0);
}

int	pars_token(t_mini *mini)
{
	t_token	*current;

	current = mini->start;
	while (current != NULL)
	{
		if (!redirection_error(current))
			return (0);
		if (!pipe_error(current))
			return (0);
		if (!missing_pipe(mini, current))
			return (0);
		current = current->next;
	}
	return (1);
}
