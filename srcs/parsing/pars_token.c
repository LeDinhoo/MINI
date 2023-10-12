/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:40:34 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 20:38:35 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*pipe_prompt(void)
{
	static char	prompt[PATH_MAX];

	ft_memset(prompt, 0, sizeof(prompt));
	ft_strcat(prompt, "pipe> ");
	return (prompt);
}

char	*here_prompt(void)
{
	static char	here_prompt[PATH_MAX];

	ft_memset(here_prompt, 0, sizeof(here_prompt));
	ft_strcat(here_prompt, "heredoc> ");
	return (here_prompt);
}

int	missing_pipe(t_mini *mini, t_token *current)
{
	char				*prompt;
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	if (!current->next && current->type == PIPE)
	{
		prompt = pipe_prompt();
		mini->input = readline(prompt);
		if (mini->input == NULL)
		{
			free_signals(mini);
			printf("mini: syntax error: unexpected end of file\nexit\n");
			exit(2);
		}
		if (g_ctrl_c_press)
			return (0);
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
