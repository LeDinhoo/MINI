/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/19 10:14:24 by hdupuy           ###   ########.fr       */
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
	tkn->ret = mini->ret;
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
			handle_single_quotes_content(tkn, str);
		else if (tkn->in_quotes == '\"' && str[tkn->end] != '\0')
			handle_double_quotes_content(tkn, str);
		else if (str[tkn->end] == '<')
			handle_less_than_operator(head, tkn, str);
		else if (str[tkn->end] == '>')
			handle_greater_than_operator(head, tkn, str);
		else if (str[tkn->end] == ';' || str[tkn->end] == '|')
			handle_semicolon_or_pipe_operator(head, tkn, str);
		else if (str[tkn->end] == ' ')
			handle_space(head, tkn, str);
		else if (str[tkn->end] == ' ' || str[tkn->end] == '\0')
			handle_end_of_string(head, tkn, str);
		tkn->end++;
	}
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
