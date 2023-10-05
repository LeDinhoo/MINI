/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:02:21 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/05 16:25:17 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_env(char **myenvp)
{
	int	len;

	len = 0;
	while (myenvp[len])
	{
		ft_printf("%s\n", myenvp[len]);
		len++;
	}
}

void	update_env(t_mini *mini)
{
	free_env(mini);
	get_path(mini);
}

void	ft_prompt(t_mini *mini)
{
	char	*prompt;

	ft_init_signals(mini->sig);
	sigaction(SIGINT, mini->sig->int_prompt, NULL);
	sigaction(SIGQUIT, mini->sig->int_prompt, NULL);
	prompt = get_prompt_str(mini);
	mini->input = readline(prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*prompt;

	(void)argc;
	(void)argv;
	mini.sig = malloc(sizeof(t_sig));
	if (!mini.sig)
		return (0);
	init_struct(&mini, envp);
	while (1)
	{
		update_env(&mini);
		// prompt = get_prompt_str(&mini);
		// mini.input = readline(prompt);
		////////////////////////////////////
		ft_prompt(&mini);
		if (mini.input == NULL)
		{
			write(1, "exit\n", 5);
			free_env(&mini);
			return (0);
		}
		//////////////////////////////////////
		else if (mini.input != NULL)
		{
			//////////////////////////////////
			if (strcmp(mini.input, "exit") == 0)
			{
				printf("exit\n");
				break ;
			}
			////////////////////////////////////
			add_history(mini.input);
			missing_quote(&mini, mini.input);
			mini.start = split_string(mini.input, &mini);
			if (pars_token(&mini))
			{
				update_token_types(&mini);
				execution(&mini);
				// print_args(&mini);
			}
			// print_list(mini.start);
			free_without_cmd(&mini);
		}
	}
	free_env(&mini);
	return (0);
}
