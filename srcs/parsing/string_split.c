/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/08/30 12:06:34 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	update_in_quotes(t_parser *parser)
{
	parser->in_quotes = !(parser->in_quotes);
	parser->start = parser->end + 1;
}

t_token	*split_string(const char *str)
{
	t_token	*head;
	t_split	*tkn;

	head = NULL;
	tkn = malloc(sizeof(t_split));
	if (tkn == NULL)
		return (NULL);
	tkn->start = 0;
	tkn->end = 0;
	tkn->length = strlen(str);
	tkn->in_quotes = 0;
	tkn->in_simple_quotes = 0;
	while (tkn->end <= tkn->length)
	{
		if (str[tkn->end] == '\'')
		{
			if (tkn->in_quotes == '\'')
			{
				tkn->in_quotes = 0;
				if (tkn->end - tkn->start > 0)
				{
					add_token_to_list(&head, &str[tkn->start], tkn->end
						- tkn->start, tkn);
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
		else if (str[tkn->end] == '\"')
		{
			if (tkn->in_quotes == '\"')
			{
				tkn->in_quotes = 0;
				if (tkn->end - tkn->start > 0)
				{
					add_token_to_list(&head, &str[tkn->start], tkn->end
						- tkn->start, tkn);
					tkn->start = tkn->end + 1;
				}
			}
			else if (!tkn->in_quotes)
			{
				tkn->in_quotes = '\"';
				tkn->start = tkn->end + 1;
			}
		}
		else if (tkn->in_quotes == '\'' && str[tkn->end] != '\0')
		{
			while (tkn->end <= tkn->length && str[tkn->end] != '\'')
				tkn->end++;
			if (tkn->end <= tkn->length)
				tkn->end--;
		}
		else if (tkn->in_quotes == '\"' && str[tkn->end] != '\0')
		{
			while (tkn->end <= tkn->length && str[tkn->end] != '\"')
				tkn->end++;
			if (tkn->end <= tkn->length)
				tkn->end--;
		}
		else if (str[tkn->end] == '<')
		{
			if (tkn->end - tkn->start > 0)
			{
				add_token_to_list(&head, &str[tkn->start], tkn->end
					- tkn->start, tkn);
			}
			if (str[tkn->end + 1] != '<')
			{
				add_token_to_list(&head, &str[tkn->end], 1, tkn);
			}
			else
			{
				tkn->tokenlength = 1;
				if (str[tkn->end + 1] == str[tkn->end])
					tkn->tokenlength = 2;
				add_token_to_list(&head, &str[tkn->end], tkn->tokenlength, tkn);
				tkn->end++;
			}
			tkn->start = tkn->end + 1;
		}
		else if (str[tkn->end] == '>')
		{
			if (tkn->end - tkn->start > 0)
			{
				add_token_to_list(&head, &str[tkn->start], tkn->end
					- tkn->start, tkn);
			}
			if (str[tkn->end + 1] != '>')
			{
				add_token_to_list(&head, &str[tkn->end], 1, tkn);
			}
			else
			{
				tkn->tokenlength = 1;
				if (str[tkn->end + 1] == str[tkn->end])
					tkn->tokenlength = 2;
				add_token_to_list(&head, &str[tkn->end], tkn->tokenlength, tkn);
				tkn->end++;
			}
			tkn->start = tkn->end + 1;
		}
		else if (str[tkn->end] == ';' || str[tkn->end] == '|')
		{
			if (tkn->end - tkn->start > 0)
			{
				add_token_to_list(&head, &str[tkn->start], tkn->end
					- tkn->start, tkn);
			}
			add_token_to_list(&head, &str[tkn->end], 1, tkn);
			tkn->start = tkn->end + 1;
		}
		else if (str[tkn->end] == ' ')
		{
			if (tkn->end - tkn->start > 0)
			{
				add_token_to_list(&head, &str[tkn->start], tkn->end
					- tkn->start, tkn);
			}
			tkn->start = tkn->end + 1;
		}
		else if (str[tkn->end] == ' ' || str[tkn->end] == '\0')
		{
			if (tkn->end - tkn->start > 0)
			{
				add_token_to_list(&head, &str[tkn->start], tkn->end
					- tkn->start, tkn);
				tkn->start = tkn->end + 1;
			}
		}
		tkn->end++;
	}
	if (tkn->in_quotes && tkn->end - tkn->start > 0)
		add_token_to_list(&head, &str[tkn->start], tkn->end - tkn->start, tkn);
	free(tkn);
	return (head);
}
