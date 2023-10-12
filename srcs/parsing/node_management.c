/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 12:52:45 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	add_node(t_token **head, char *str, int type)
{
	t_token	*node;
	t_token	*current;

	node = malloc(sizeof(t_token));
	node->str = ft_strdup(str);
	if ((node->str[0] == '\'' && node->str[1] == '\0')
		|| (node->str[0] == '\"'
			&& node->str[1] == '\0'))
		node->str[0] = ' ';
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	if (*head == NULL)
		*head = node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
		node->prev = current;
	}
}

void	add_token_to_list(t_token **head, const char *start, int tokenLength,
		t_split *tkn)
{
	char	*token;
	char	*substituted_token;

	token = malloc(tokenLength + 1);
	strncpy(token, start, tokenLength);
	token[tokenLength] = '\0';
	substituted_token = substitute_variable_value(token, tkn);
	if (substituted_token[0] == '\0')
	{
		free(token);
		return ;
	}
	substituted_token = substitute_quote(substituted_token);
	add_node(head, substituted_token, determine_token_type(substituted_token,
			tkn));
	tkn->in_simple_quotes = 0;
	free(substituted_token);
	free(token);
}

void	add_cmd_node(t_cmd *node, t_cmd **head)
{
	t_cmd	*current;

	if (*head == NULL)
		*head = node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
	}
}
