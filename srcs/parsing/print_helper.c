/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/08/31 19:27:17 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_list(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		if (current->prev)
			printf("Token: %s, Type: %d\n", current->str, current->type);
		else
			printf("Token: %s, Type: %d\n", current->str, current->type);
		current = current->next;
	}
}
