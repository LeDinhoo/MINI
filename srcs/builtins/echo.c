/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:18:50 by hdupuy            #+#    #+#             */
/*   Updated: 2023/07/13 10:20:41 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_token	*echo_build(t_token *head)
{
	t_token	*current;
	int		newline;

	current = head;
	newline = 1;
	if (current && ft_strcmp(current->str, "echo") == 0)
		current = current->next;
	if (current && ft_strcmp(current->str, "-n") == 0)
	{
		newline = 0;
		current = current->next;
	}
	while (current && current->type != 7)
	{
		printf("%s", current->str);
		if (current->next && current->next->type != 7)
			printf(" ");
		current = current->next;
	}
	if (newline)
		printf("\n");
	return (current);
}
