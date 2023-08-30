/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/08/30 12:05:40 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	determine_token_type(const char *str)
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
	else
	{
		if (*str == '\0' || *str == '|' || *str == ';')
			return (CMD);
		else
			return (ARG);
	}
}

char	*find_dollar_value(char *token, int i)
{
	char	*variablename;
	int		var_len;
	int		j;
	int		is_find;

	is_find = 0;
	var_len = 0;
	j = i;
	variablename = NULL;
	while (token[i] && token[i] != ' ')
	{
		if (token[i] == '$')
		{
			if (is_find == 0)
				is_find = 1;
			else
				break ;
		}
		var_len++;
		i++;
	}
	i = j;
	variablename = ft_calloc(sizeof(char), var_len + 1);
	variablename = strncpy(variablename, &token[i], var_len);
	return (variablename);
}

int	get_count(t_replace *rep)
{
	char	*ins;
	char	*tmp;

	ins = rep->str;
	rep->count = 0;
	tmp = strstr(ins, rep->str1);
	while (tmp != NULL)
	{
		++rep->count;
		ins = tmp + rep->len_substr1;
		tmp = strstr(ins, rep->str1);
	}
	return (rep->count);
}

char	*allocate_memory(t_replace *rep)
{
	rep->resultat = malloc(strlen(rep->str) + (rep->len_substr2
			- rep->len_substr1) * rep->count + 1);
	if (!rep->resultat)
	{
		printf("Erreur d'allocation de mémoire.\n");
		exit(1);
	}
	return (rep->resultat);
}

void	replace_str(t_replace *rep)
{
	char	*ins;
	char	*tmp;
	int		len_str;

	tmp = rep->resultat;
	while (rep->count--)
	{
		ins = strstr(rep->str, rep->str1);
		len_str = ins - rep->str;
		tmp = strncpy(tmp, rep->str, len_str) + len_str;
		tmp = strcpy(tmp, rep->str2) + rep->len_substr2;
		rep->str += len_str + rep->len_substr1;
	}
	strcpy(tmp, rep->str);
}

char	*replace_substring(char *str, char *str1, char *str2)
{
	t_replace	rep;

	if (!str1)
		return (str);
	rep.len_substr1 = strlen(str1);
	if (!rep.len_substr1)
		return (str);
	if (!str2)
		str2 = "";
	rep.len_substr2 = strlen(str2);
	rep.str = str;
	rep.str1 = str1;
	rep.str2 = str2;
	get_count(&rep);
	allocate_memory(&rep);
	replace_str(&rep);
	return (rep.resultat);
}

char	*substitute_variable_value(char *token, t_split *tkn)
{
	t_switch	swap;

	swap.is_switch = 0;
	swap.substitutedtoken = token;
	while (ft_strchr(swap.substitutedtoken, '$') != NULL
		&& tkn->in_simple_quotes == 0)
	{
		swap.variablename = find_dollar_value(swap.substitutedtoken,
			ft_strichr(swap.substitutedtoken, '$'));
		swap.variablevalue = getenv(swap.variablename + 1);
		swap.substitutedtoken = replace_substring(swap.substitutedtoken,
			swap.variablename, swap.variablevalue);
		free(swap.variablename);
		swap.is_switch = 1;
	}
	if (swap.is_switch == 0)
		swap.substitutedtoken = strdup(token);
	return (swap.substitutedtoken);
}

void	add_token_to_list(t_token **head, const char *start, int tokenLength,
		t_split *tkn)
{
	char	*token;
	char	*substituted_token;

	token = malloc(tokenLength + 1);
	strncpy(token, start, tokenLength);
	token[tokenLength] = '\0';
	substituted_token = substitute_variable_value(token, tkn);
	add_node(head, substituted_token, determine_token_type(substituted_token));
	tkn->in_simple_quotes = 0;
	free(substituted_token);
	free(token);
}
