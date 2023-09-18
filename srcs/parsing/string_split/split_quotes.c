/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:38:00 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 16:38:27 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handle_single_quotes(t_token **head, t_split *tkn, const char *str)
{
	if (tkn->in_quotes == '\'')
	{
		tkn->in_quotes = 0;
		if (tkn->end - tkn->start > 0)
		{
			add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start,
				tkn);
			tkn->start = tkn->end + 1;
		}
	}
	else if (!tkn->in_quotes)
	{
		tkn->in_quotes = '\'';
		tkn->in_simple_quotes = 1;
		tkn->start = tkn->end + 1;
	}
}

void	handle_double_quotes(t_token **head, t_split *tkn, const char *str)
{
	if (tkn->in_quotes == '\"')
	{
		tkn->in_quotes = 0;
		if (tkn->end - tkn->start > 0)
		{
			add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start,
				tkn);
			tkn->start = tkn->end + 1;
		}
	}
	else if (!tkn->in_quotes)
	{
		tkn->in_quotes = '\"';
		tkn->start = tkn->end + 1;
	}
}

void	handle_single_quotes_content(t_split *tkn, const char *str)
{
	while (tkn->end <= tkn->length && str[tkn->end] != '\'')
		tkn->end++;
	if (tkn->end <= tkn->length)
		tkn->end--;
}

void	handle_double_quotes_content(t_split *tkn, const char *str)
{
	while (tkn->end <= tkn->length && str[tkn->end] != '\"')
		tkn->end++;
	if (tkn->end <= tkn->length)
		tkn->end--;
}
