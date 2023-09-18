/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:39:24 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 16:40:52 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handle_less_than_operator(t_token **head, t_split *tkn, const char *str)
{
	if (tkn->end - tkn->start > 0)
	{
		add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start, tkn);
	}
	if (str[tkn->end + 1] != '<')
	{
		add_token_to_list(head, &str[tkn->end], 1, tkn);
	}
	else
	{
		tkn->tokenlength = 1;
		if (str[tkn->end + 1] == str[tkn->end])
			tkn->tokenlength = 2;
		add_token_to_list(head, &str[tkn->end], tkn->tokenlength, tkn);
		tkn->end++;
	}
	tkn->start = tkn->end + 1;
}

void	handle_greater_than_operator(t_token **head, t_split *tkn,
		const char *str)
{
	if (tkn->end - tkn->start > 0)
	{
		add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start, tkn);
	}
	if (str[tkn->end + 1] != '>')
	{
		add_token_to_list(head, &str[tkn->end], 1, tkn);
	}
	else
	{
		tkn->tokenlength = 1;
		if (str[tkn->end + 1] == str[tkn->end])
			tkn->tokenlength = 2;
		add_token_to_list(head, &str[tkn->end], tkn->tokenlength, tkn);
		tkn->end++;
	}
	tkn->start = tkn->end + 1;
}

void	handle_semicolon_or_pipe_operator(t_token **head, t_split *tkn,
		const char *str)
{
	if (tkn->end - tkn->start > 0)
	{
		add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start, tkn);
	}
	add_token_to_list(head, &str[tkn->end], 1, tkn);
	tkn->start = tkn->end + 1;
}

void	handle_space(t_token **head, t_split *tkn, const char *str)
{
	if (tkn->end - tkn->start > 0)
	{
		add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start, tkn);
	}
	tkn->start = tkn->end + 1;
}

void	handle_end_of_string(t_token **head, t_split *tkn, const char *str)
{
	if (tkn->end - tkn->start > 0)
	{
		add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start, tkn);
		tkn->start = tkn->end + 1;
	}
}
