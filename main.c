/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:02:21 by hdupuy            #+#    #+#             */
/*   Updated: 2023/08/31 18:18:39 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(void)
{
	t_mini	mini;
	char	*prompt;

	init_struct(&mini);
	while (1)
	{
		prompt = get_prompt_str();
		mini.input = readline(prompt);
		if (mini.input != NULL)
		{
			if (strcmp(mini.input, "exit") == 0)
				break ;
			add_history(mini.input);
			mini.start = split_string(mini.input, &mini);
			update_token_types(&mini);
			if (pars_token(&mini))
			{
				builtin_exec(&mini);
				execution(&mini);
				print_args(&mini);
			}
			print_list(mini.start);
			free_list(mini.start);
			free_cmd(&mini);
			free(mini.input);
			mini.start = NULL;
		}
	}
	free_env(&mini);
	return (0);
}

// int	main(void)
// {
// 	t_mini	mini;
// 	char	*prompt;

// 	init_struct(&mini);
// 	while (1)
// 	{
// 		prompt = get_prompt_str();
// 		mini.input = readline(prompt);
// 		if (mini.input != NULL)
// 		{
// 			if (strcmp(mini.input, "exit") == 0)
// 				break ;
// 			add_history(mini.input);
// 			mini.start = split_string(mini.input);
// 			update_token_types(&mini);
// 			print_list(mini.start);
// 			free_list(mini.start);
// 			free(mini.input);
// 		}
// 	}
// 	free_env(&mini);
// 	return (0);
// }
