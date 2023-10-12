/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:57:34 by cbacquet          #+#    #+#             */
/*   Updated: 2023/10/12 12:36:37 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	init_split(t_split *tkn, t_mini *mini, const char *str)
{
	tkn->start = 0;
	tkn->end = 0;
	tkn->length = strlen(str);
	tkn->in_quotes = 0;
	tkn->in_simple_quotes = 0;
	tkn->equal = 0;
	tkn->myenvp = mini->envp;
	tkn->shenvp = mini->sh_envp;
	tkn->ret = mini->ret;
}

t_token	*split_string(const char *str, t_mini *mini)
{
	t_token	*head;
	t_split	*tkn;

	if (mini->start == NULL)
		head = NULL;
	else
		head = mini->start;
	tkn = malloc(sizeof(t_split));
	if (tkn == NULL)
		return (NULL);
	init_split(tkn, mini, str);
	process_string(str, &head, tkn);
	if (tkn->in_quotes && tkn->end - tkn->start > 0)
		add_token_to_list(&head, &str[tkn->start], tkn->end - tkn->start, tkn);
	free(tkn);
	return (head);
}

void	handle_double_quotes_content(t_token **head, t_split *tkn,
		const char *str)
{
	while (tkn->end <= tkn->length
		&& (ft_strichr("<>;| ", str[tkn->end + 1]) == -1)
		&& str[tkn->end + 1] != '\0')
	{
		tkn->end++;
	}
	add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start + 1, tkn);
	tkn->end++;
	tkn->start = tkn->end + 1;
	tkn->in_quotes = 0;
}
