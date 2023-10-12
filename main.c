/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:02:21 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 14:56:04 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_env(char **myenvp)
{
	int	len;

	len = 0;
	while (myenvp && myenvp[len])
	{
		if (ft_strchr(myenvp[len], '=') != NULL)
			ft_printf("%s\n", myenvp[len]);
		len++;
	}
}

void	update_env(t_mini *mini)
{
	free_env(mini);
	get_path(mini);
	if (!get_env("PWD", mini->envp))
		ft_printf("PWD environment variable not set");
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

void	go_cmd(t_mini *mini)
{
	add_history(mini->input);
	missing_quote(mini);
	mini->start = split_string(mini->input, mini);
	if (pars_token(mini))
	{
		update_token_types(mini);
		execution(mini);
	}
	// print_list(mini->start);
	free_without_cmd(mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	mini.sig = malloc(sizeof(t_sig));
	if (!mini.sig)
		return (0);
	init_struct(&mini, envp);
	while (1)
	{
		update_env(&mini);
		ft_prompt(&mini);
		if (mini.input != NULL)
		{
			go_cmd(&mini);
		}
		else
		{
			printf("exit\n");
			free_signals(&mini);
			free_env(&mini);
			return (0);
		}
	}
	free_env(&mini);
	return (0);
}
