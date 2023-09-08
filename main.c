/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:02:21 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/08 10:56:55 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void ft_set_signals(void)
{
	struct sigaction	act;
	
	ft_memset(&act, 0, sizeof(struct sigaction));
	rl_on_new_line();
	rl_redisplay();
}

void	ft_handle_signal()
{
	rl_on_new_line();
}

ft_ignore_quit_signal()

void	set_signals_handle(void)
{
	struct sigaction act;
	
	ft_ignore_quit_signal();
	ft_memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = &ft_handle_signal;
}

char *ft_prompt(t_mini *mini)
{
	char *prompt;
	
	ft_set_signals();
	prompt = get_prompt_str();
	mini->input = readline(prompt);
	ft_set_signals_handle();
}

int	main(void)
{
	t_mini	mini;
	char	*prompt;

	init_struct(&mini);
	while (1)
	{
		
		prompt = get_prompt_str();
		mini.input = readline(prompt);
		// ft_prompt(mini);
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
