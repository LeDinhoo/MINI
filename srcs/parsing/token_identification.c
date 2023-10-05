/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/03 13:58:48 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	determine_token_type(const char *str, t_split *tkn)
{
	if (strcmp(str, "") == 0)
		return (EMPTY);
	else if (strcmp(str, ";") == 0)
		return (END);
	else if (strcmp(str, "|") == 0)
		return (PIPE);
	else if (strcmp(str, "<") == 0)
		return (INPUT);
	else if (strcmp(str, ">") == 0)
		return (TRUNC);
	else if (strcmp(str, ">>") == 0)
		return (APPEND);
	else if (strcmp(str, "<<") == 0)
		return (HEREDOC);
	else if (tkn->equal == 1)
		return (EXPORT);
	else
	{
		if (*str == '\0' || *str == '|' || *str == ';')
			return (CMD);
		else
			return (ARG);
	}
}

int	var_len(char *token, int i, int var_len)
{
	int	is_find;

	is_find = 0;
	while (token[i] && ((ft_isalpha(token[i]) == 1) || token[i] == '$'
			|| token[i] == '?'))
	{
		if (token[i] == '$')
		{
			if (i > 0 && token[i - 1] == '$')
				var_len++;
			if (is_find == 0)
				is_find = 1;
			else
				break ;
		}
		if (token[i] == '?')
		{
			if (i > 0 && token[i - 1] == '$')
				var_len++;
			break ;
		}
		var_len++;
		i++;
	}
	return (var_len);
}

char	*find_dollar_value(char *token, int i)
{
	char	*variablename;
	int		len;
	int		j;

	len = 0;
	j = i;
	variablename = NULL;
	len = var_len(token, i, len);
	i = j;
	variablename = ft_calloc(sizeof(char), len + 1);
	variablename = strncpy(variablename, &token[i], len);
	return (variablename);
}
