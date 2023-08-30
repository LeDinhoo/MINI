/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/07/12 14:39:25 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	add_node(t_token **head, char *str, int type)
{
	t_token	*node;
	t_token	*current;

	node = malloc(sizeof(t_token));
	node->str = ft_strdup(str);
	if ((node->str[0] == '\'' && node->str[1] == '\0') || (node->str[0] == '\"'
			&& node->str[1] == '\0'))
		node->str[0] = ' ';
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	if (*head == NULL)
	{
		*head = node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = node;
		node->prev = current;
	}
}
