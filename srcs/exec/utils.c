/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:32:22 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 15:21:59 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_only(t_mini *mini)
{
	t_cmd	*current;
	int		i;

	i = 0;
	current = mini->cmd_tab;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

int	cmd_numbers(t_cmd *cmd)
{
	t_cmd	*current;
	int		nb;

	current = cmd;
	nb = 0;
	while (current != NULL)
	{
		current = current->next;
		nb++;
	}
	return (nb);
}

void	set_last_cmd(t_mini *mini)
{
	t_cmd	*current;
	t_cmd	*last;

	current = mini->cmd_tab;
	while (current)
	{
		last = current;
		current = current->next;
	}
	last->is_last = 1;
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

int	ft_isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
