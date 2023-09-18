/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:21:21 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 14:18:46 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	redirection_error(t_token *current)
{
	if (!current->next && (current->type == TRUNC || current->type == APPEND
			|| current->type == INPUT || current->type == HEREDOC))
	{
		print_error(LINE_ERR);
		return (0);
	}
	return (1);
}

int	pipe_error(t_token *current)
{
	if (!current->prev && current->type == PIPE)
	{
		print_error(PIPE_ERR);
		return (0);
	}
	if (current->next && current->prev)
	{
		if ((current->prev->type == PIPE || current->next->type == PIPE)
			&& current->type == PIPE)
		{
			print_error(PIPE_ERR);
			return (0);
		}
	}
	return (1);
}
