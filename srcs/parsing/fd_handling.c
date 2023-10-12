/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:27:11 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 19:56:23 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
		g_ctrl_c_press = 1;
}

void	ft_putstr_heredoc(char *s, int heredoc_fd)
{
	ft_putstr_fd(s, heredoc_fd);
	ft_putstr_fd("\n", heredoc_fd);
	free(s);
}

void	init_heredoc(t_mini *mini)
{
	mini->is_here_doc = 1;
	mini->here_doc_fd = 0;
	mini->here_doc_fd = open("/tmp/.pipex_here_doc",
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	setup_here_doc(t_mini *mini, char *limiter)
{
	char				*s1;
	char				*prompt;
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	init_heredoc(mini);
	if (mini->here_doc_fd < 0)
		return (printf("ERROR"), (void)0);
	while (1)
	{
		prompt = here_prompt();
		s1 = readline(prompt);
		if (!s1)
			return (printf(H_D_DELIM "(wanted '%s')\n", limiter), (void)0);
		if (g_ctrl_c_press)
			return (g_ctrl_c_press = 0, free(s1), close(mini->here_doc_fd),
				(void)0);
		if (ft_strncmp(s1, limiter, ft_strlen(limiter)) == 0)
			return (free(s1), (void)0);
		ft_putstr_heredoc(s1, mini->here_doc_fd);
	}
	close(mini->here_doc_fd);
}
