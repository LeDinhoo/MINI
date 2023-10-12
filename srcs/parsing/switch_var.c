/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:19:51 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 12:53:37 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handle_last_return_value(t_switch *swap, t_split *tkn)
{
	swap->variablevalue = ft_itoa(tkn->ret);
	swap->substitutedtoken = replace_substring(swap->substitutedtoken,
			swap->variablename, swap->variablevalue);
	swap->is_switch = 1;
	free(swap->variablevalue);
}

void	handle_classic_env_value(t_switch *swap, t_split *tkn)
{
	swap->variablevalue = get_env(swap->variablename + 1, tkn->myenvp);
	if (swap->variablevalue == NULL)
		swap->variablevalue = get_env(swap->variablename + 1, tkn->shenvp);
	swap->substitutedtoken = replace_substring(swap->substitutedtoken,
			swap->variablename, swap->variablevalue);
	swap->is_switch = 1;
}

int	replace_quote(t_switch *swap, int is_open, int i)
{
	if (is_open != '\"' && swap->substitutedtoken[i] == '\'')
	{
		if (is_open != '\'')
		{
			swap->variablename = "'";
			swap->substitutedtoken = replace_substring(swap->substitutedtoken,
					swap->variablename, swap->variablevalue);
			is_open = '\'';
		}
		else
			is_open = 0;
	}
	if (is_open != '\'' && swap->substitutedtoken[i] == '\"')
	{
		if (is_open != '\"')
		{
			swap->variablename = "\"";
			swap->substitutedtoken = replace_substring(swap->substitutedtoken,
					swap->variablename, swap->variablevalue);
			is_open = '\"';
		}
		else
			is_open = 0;
	}
	return (is_open);
}

char	*substitute_quote(char *token)
{
	t_switch	swap;
	int			i;
	int			is_open;

	is_open = 0;
	i = 0;
	swap.variablevalue = "";
	swap.substitutedtoken = token;
	while (swap.substitutedtoken[i])
	{
		is_open = replace_quote(&swap, is_open, i);
		i++;
	}
	return (swap.substitutedtoken);
}
