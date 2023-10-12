/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:22:43 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 14:13:59 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_option(t_token *current)
{
	if (current->str[0] == '-')
	{
		ft_printf("export: option not allowed in this context\n");
		return (0);
	}
	return (1);
}

void	handle_var_location(t_mini *mini, t_token *cur_tkn)
{
	char	*var_name;

	if (cur_tkn->type == EXPORT || cur_tkn->type == ARG)
	{
		var_name = find_var_name(cur_tkn->str);
		if (get_env(var_name, mini->envp) == NULL)
			add_var_to_env(mini, cur_tkn->str);
		else
			modify_var_value(mini, cur_tkn->str, var_name);
	}
	else if (get_env(cur_tkn->str, mini->sh_envp))
	{
		var_name = get_var_str(mini->sh_envp, cur_tkn->str);
		if (get_env(cur_tkn->str, mini->envp) == NULL)
			add_var_to_env(mini, var_name);
		else
			modify_var_value(mini, var_name, cur_tkn->str);
	}
}

int	print_export(char **myenvp)
{
	int	len;

	len = 0;
	while (myenvp && myenvp[len])
	{
		ft_printf("declare -x %s\n", myenvp[len]);
		len++;
	}
	return (0);
}

int	export_build(t_mini *mini)
{
	t_token *cur_tkn;

	cur_tkn = mini->start;
	if (!cur_tkn->next)
	{
		print_export(mini->envp);
		return (0);
	}
	while (cur_tkn)
	{
		if (is_option(cur_tkn) == 0)
		{
			if (cur_tkn->next)
				cur_tkn = cur_tkn->next;
			else
				break ;
		}
		handle_var_location(mini, cur_tkn);
		cur_tkn = cur_tkn->next;
	}
	return (0);
}