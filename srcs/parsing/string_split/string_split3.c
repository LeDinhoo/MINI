/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:17:07 by cbacquet          #+#    #+#             */
/*   Updated: 2023/10/12 20:31:10 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*quote_prompt(void)
{
	static char	here_prompt[PATH_MAX];

	ft_memset(here_prompt, 0, sizeof(here_prompt));
	ft_strcat(here_prompt, "dquote> ");
	return (here_prompt);
}

int	quotes_checking(const char *str, int is_open, int i)
{
	if (is_open != '\"' && str[i] == '\'')
	{
		if (is_open == '\'')
			is_open = 0;
		else
			is_open = '\'';
	}
	if (is_open != '\'' && str[i] == '\"')
	{
		if (is_open == '\"')
			is_open = 0;
		else
			is_open = '\"';
	}
	return (is_open);
}

int	is_quotes_open(const char *str)
{
	int	i;
	int	is_open;

	is_open = 0;
	i = 0;
	while (str[i])
	{
		is_open = quotes_checking(str, is_open, i);
		i++;
	}
	if (is_open == 0)
		return (0);
	return (1);
}

void	missing_quote(t_mini *mini)
{
	struct sigaction	sa;
	char				*prompt;
	char				*new_str;
	char				*new_input;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	while (is_quotes_open(mini->input))
	{
		prompt = quote_prompt();
		new_str = readline(prompt);
		if (!new_str)
			return (printf(Q_DELIM " (wanted « %c »)\n", '"'), (void)0);
		if (g_ctrl_c_press)
			return (g_ctrl_c_press = 0, (void)0);
		new_str = strjoin_bis("\n", new_str);
		new_str = ft_strjoin(mini->input, new_str);
		mini->input = ft_strdup(new_str);
		free(new_str);
	}
	return ;
}
