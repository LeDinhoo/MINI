/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:49:46 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/10 22:10:48 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
	rep->resultat = malloc(ft_strlen(rep->str) + (rep->len_substr2
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

void	free_without_cmd(t_mini *mini)
{
	free_list(mini->start);
	free_cmd(mini);
	free(mini->input);
	mini->start = NULL;
}
