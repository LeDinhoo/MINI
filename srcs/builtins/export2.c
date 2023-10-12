/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:22:43 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 17:41:26 by hdupuy           ###   ########.fr       */
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

int	is_in_export(const char *name, char **myenvp)
{
	int		i;
	char	*env_entry;

	i = 0;
	if (!myenvp || !name)
		return (1);
	while (myenvp[i])
	{
		env_entry = myenvp[i];
		if (ft_strncmp(env_entry, name, strlen(name)) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	handle_var_location(t_mini *mini, t_token *cur_tkn)
{
	char	*var_name;

	var_name = cur_tkn->str;
	var_name = find_var_name(cur_tkn->str);
	if (ft_strlen(var_name) != 0 && is_in_export(var_name, mini->envp) == 0)
	{
		if (ft_strchr(cur_tkn->str, '=') != NULL)
			modify_var_value(mini, cur_tkn->str, var_name);
	}
	else
	{
		if (cur_tkn->str[0] == '=')
		{
			ft_printf("mini: export: « %s » : invalid identifier\n",
				cur_tkn->str);
		}
		else
		{
			if (is_in_export(var_name, mini->sh_envp) == 0)
				add_var_to_env(mini, get_var_str(mini->sh_envp, var_name));
			else
				add_var_to_env(mini, cur_tkn->str);
		}
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
	t_token	*cur_tkn;

	cur_tkn = mini->start;
	if (!cur_tkn->next)
	{
		print_export(mini->envp);
		return (0);
	}
	cur_tkn = cur_tkn->next;
	while (cur_tkn && cur_tkn->type != TRUNC && cur_tkn->type != APPEND
		&& cur_tkn->type != INPUT && cur_tkn->type != PIPE
		&& cur_tkn->type != END && cur_tkn->type != HEREDOC)
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
