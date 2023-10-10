/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/06 11:16:16 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	update_in_quotes(t_parser *parser)
{
	parser->in_quotes = !(parser->in_quotes);
	parser->start = parser->end + 1;
}

void	init_split(t_split *tkn, t_mini *mini, const char *str)
{
	tkn->start = 0;
	tkn->end = 0;
	tkn->length = strlen(str);
	tkn->in_quotes = 0;
	tkn->in_simple_quotes = 0;
	tkn->equal = 0;
	tkn->myenvp = mini->envp;
	tkn->shenvp = mini->sh_envp;
	tkn->ret = mini->ret;
}

void	handle_equal(t_token **head, t_split *tkn, const char *str)
{
	tkn->equal = 1;
	while ((ft_strichr("<>;| ", str[tkn->end + 1]) == -1) && str[tkn->end + 1])
		tkn->end++;
	if (tkn->end - tkn->start > 0)
	{
		add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start + 1,
			tkn);
		tkn->equal = 0;
	}
	tkn->start = tkn->end + 1;
}

void	process_string(const char *str, t_token **head, t_split *tkn)
{
	while (tkn->end <= tkn->length)
	{
		if ((str[tkn->end] == ':' || str[tkn->end] == '!') && tkn->length == 1)
			return ;
		if (str[tkn->end] == '\'')
			handle_single_quotes(head, tkn, str);
		else if (str[tkn->end] == '\"')
			handle_double_quotes(head, tkn, str);
		else if (tkn->in_quotes == '\'' && str[tkn->end] != '\0')
			handle_single_quotes_content(head, tkn, str);
		else if (tkn->in_quotes == '\"' && str[tkn->end] != '\0')
			handle_double_quotes_content(head, tkn, str);
		else if (str[tkn->end] == '<')
			handle_less_than_operator(head, tkn, str);
		else if (str[tkn->end] == '>')
			handle_greater_than_operator(head, tkn, str);
		else if (str[tkn->end] == ';' || str[tkn->end] == '|')
			handle_semicolon_or_pipe_operator(head, tkn, str);
		else if (str[tkn->end] == '=')
			handle_equal(head, tkn, str);
		else if (str[tkn->end] == ' ')
			handle_space(head, tkn, str);
		else if (str[tkn->end] == ' ' || str[tkn->end] == '\0')
			handle_end_of_string(head, tkn, str);
		tkn->end++;
	}
}

char	*quote_prompt(void)
{
	static char	here_prompt[PATH_MAX];

	memset(here_prompt, 0, sizeof(here_prompt));
	strcat(here_prompt, "dquote> ");
	return (here_prompt);
}

int	missing_quote(t_mini *mini, const char *str)
{
	int		i;
	int		is_open;
	char	*prompt;
	char	*new_str;

	is_open = 0;
	i = 0;
	while (str[i])
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
		i++;
	}
	if (is_open != 0)
	{
		prompt = quote_prompt();
		new_str = readline(prompt);
		mini->input = strcat(mini->input, "\n");
		mini->input = strcat(mini->input, new_str);
		free(new_str);
		missing_quote(mini, mini->input);
	}
	return (1);
}

t_token	*split_string(const char *str, t_mini *mini)
{
	t_token	*head;
	t_split	*tkn;

	if (mini->start == NULL)
		head = NULL;
	else
		head = mini->start;
	tkn = malloc(sizeof(t_split));
	if (tkn == NULL)
		return (NULL);
	init_split(tkn, mini, str);
	process_string(str, &head, tkn);
	if (tkn->in_quotes && tkn->end - tkn->start > 0)
		add_token_to_list(&head, &str[tkn->start], tkn->end - tkn->start, tkn);
	free(tkn);
	return (head);
}
