/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:17:07 by cbacquet          #+#    #+#             */
/*   Updated: 2023/10/12 12:41:15 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*quote_prompt(void)
{
	static char	here_prompt[PATH_MAX];

	memset(here_prompt, 0, sizeof(here_prompt));
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

void	new_input(t_mini *mini)
{
	char	*prompt;
	char	*new_str;
	char	*new_input;

	prompt = quote_prompt();
	new_str = readline(prompt);
	new_input = ft_calloc((ft_strlen(new_str) + ft_strlen(mini->input)) + 1,
			sizeof(char));
	ft_strcat(new_input, mini->input);
	ft_strcat(new_input, "\n");
	ft_strcat(new_input, new_str);
	free(new_str);
	free(mini->input);
	mini->input = NULL;
	mini->input = ft_strdup(new_input);
	free(new_input);
}

int	missing_quote(t_mini *mini)
{
	while (is_quotes_open(mini->input))
		new_input(mini);
	return (0);
}
