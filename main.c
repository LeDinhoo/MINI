/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:02:21 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/12 16:24:21 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// void	ft_init_quit_handle(t_sig *sig)
// {
// 	sig->quit_prompt->sa_handler = SIG_IGN;
// 	sig->quit_prompt->sa_flags = SA_RESTART;
// 	sigemptyset(&sig->quit_prompt->sa_mask);
// }

// void	ft_handle_signal(int sig_prompt)
// {
// 	(void)sig_prompt;
// 	write(1, "\n", 1);
// 	// ft_dprintf(STDOUT_FILENO, "\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	ft_handle_signal_heredoc(int sig_heredoc)
// {
// 	(void)sig_heredoc;
// 	close(STDIN_FILENO);
// 	write(1, "\n", 1);
// }

// void	ft_set_signals_handle(t_sig *sig)
// {
// 	sig->int_prompt->sa_handler = ft_handle_signal;
// 	sig->int_prompt->sa_flags = SA_RESTART;
// 	sigemptyset(&sig->int_prompt->sa_mask);
// 	sig->int_exec->sa_handler = SIG_IGN;
// 	sig->int_exec->sa_flags = SA_RESTART;
// 	sigemptyset(&sig->int_exec->sa_mask);
// 	sig->int_exec->sa_handler = SIG_DFL;
// 	sig->int_exec->sa_flags = SA_RESTART;
// 	sigemptyset(&sig->int_exec->sa_mask);
// 	sig->here_doc->sa_handler = ft_handle_signal_heredoc;
// 	sig->here_doc->sa_flags = SA_RESTART;
// 	sigemptyset(&sig->here_doc->sa_mask);
	
// }

// void	ft_init_signals(t_sig *sig)
// {
// 	sig->int_prompt = calloc(1, sizeof(struct sigaction));
// 	sig->int_exec = calloc(1, sizeof(struct sigaction));
// 	// sig->int_parent = calloc(1, sizeof(struct sigaction));
// 	sig->here_doc = calloc(1, sizeof(struct sigaction));
// 	sig->quit_prompt = calloc(1, sizeof(struct sigaction));
// 	sig->quit_exec = calloc(1, sizeof(struct sigaction));
// 	// sig->quit_parent = calloc(1, sizeof(struct sigaction));
// 	// ft_check_malloc(sig);
// 	ft_init_quit_handle(sig);
// 	ft_set_signals_handle(sig);
// }

void	ft_prompt(t_mini *mini)
{
	char *prompt;
	
	ft_init_signals(mini->sig);
	sigaction(SIGINT, mini->sig->int_prompt, NULL);
	// sigaction(SIGQUIT, mini->sig->int_prompt, NULL);
	prompt = get_prompt_str();
	mini->input = readline(prompt);
}

int	main(void)
{
	t_mini	mini;
	char	*prompt;

	mini.sig = malloc(sizeof(t_sig));
	init_struct(&mini);
	while (1)
	{
		
		// ft_init_signals(mini.sig);
		// prompt = get_prompt_str();
		// mini.input = readline(prompt);
		ft_prompt(&mini);
		if (mini.input == NULL)
		{
			write(1, "exit\n", 5);
			free_env(&mini);
			return(0);
		}
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
