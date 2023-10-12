/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processing2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:22:37 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 18:25:48 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handle_exportable_type(t_token *current, int only_nine, int is_export,
		t_mini *mini)
{
	if (current->type == EXPORT)
	{
		if (only_nine == 1)
		{
			if (current->prev && current->prev->type == CMD)
				current->type = ARG;
			else
				current->type = 0;
		}
		if (is_export == 0 && current->next && current->next->type == ARG)
			current->next->type = CMD;
	}
	if (current->type == EXPORT)
		add_tmp_var(mini, current);
}

void	export_and_only(t_mini *mini, int *is_export, int *only_nine)
{
	t_token	*current;

	current = mini->start;
	while (current)
	{
		if (ft_strcmp(current->str, "export") == 0)
			*is_export = 1;
		if (current->type != EXPORT)
			*only_nine = 1;
		current = current->next;
	}
}
