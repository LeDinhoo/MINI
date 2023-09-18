/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:19:51 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 15:21:25 by hdupuy           ###   ########.fr       */
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

void	handle_classic_env_value(t_switch *swap)
{
	swap->variablevalue = getenv(swap->variablename + 1);
	swap->substitutedtoken = replace_substring(swap->substitutedtoken,
			swap->variablename, swap->variablevalue);
	swap->is_switch = 1;
}

char	*substitute_variable_value(char *token, t_split *tkn)
{
	t_switch	swap;
	int			dollarpos;

	swap.is_switch = 0;
	swap.substitutedtoken = token;
	while (ft_strchr(swap.substitutedtoken, '$') != NULL
		&& tkn->in_simple_quotes == 0)
	{
		swap.variablename = find_dollar_value(swap.substitutedtoken,
				ft_strichr(swap.substitutedtoken, '$'));
		if (ft_strcmp(swap.variablename, "$?") == 0)
			handle_last_return_value(&swap, tkn);
		else
			handle_classic_env_value(&swap);
		free(swap.variablename);
		dollarpos = ft_strichr(swap.substitutedtoken, '$');
		if (swap.substitutedtoken[dollarpos + 1] == '\0')
			break ;
	}
	if (swap.is_switch == 0)
		swap.substitutedtoken = strdup(token);
	return (swap.substitutedtoken);
}
