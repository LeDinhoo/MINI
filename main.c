/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:02:21 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/21 20:05:32 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*char **ft_init_shell_env(char **envp)
{
	char	**new_envp;
	char	*pwd;
	char	*old_pwd;
	char	*shlvl;

	if (envp[0])
		new_envp = ft_dup_array(envp, false, true);
	else
	{
		new_envp = ft_calloc(5, sizeof(char *));
		pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
		new_envp[0] = pwd;
		old_pwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
		new_envp[1] = old_pwd;
		shlvl = ft_strdup("SHLVL=1");
		new_envp[2] = shlvl;
		new_envp[3] = ft_strdup("PATH=");
	}
	return (envp);
}*/

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*prompt;

	(void)argc;
	(void)argv;
	init_struct(&mini, envp);
	//mini.envp = ft_init_shell_env(envp);
	while (1)
	{
		prompt = get_prompt_str(&mini);
		mini.input = readline(prompt);
		if (mini.input != NULL)
		{
			add_history(mini.input);
			mini.start = split_string(mini.input, &mini);
			if (pars_token(&mini))
			{
				update_token_types(&mini);
				builtin_exec(&mini);
				execution(&mini);
			}
			free_without_cmd(&mini);
		}
	}
	free_env(&mini);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_mini	mini;
// 	char	*prompt;

// 	(void)argc;
// 	(void)argv;
// 	init_struct(&mini, envp);
// 	while (1)
// 	{
// 		prompt = get_prompt_str(&mini);
// 		mini.input = readline(prompt);
// 		if (mini.input != NULL)
// 		{
// 			if (strcmp(mini.input, "exit") == 0)
// 				break ;
// 			add_history(mini.input);
// 			mini.start = split_string(mini.input, &mini);
// 			if (pars_token(&mini))
// 			{
// 				update_token_types(&mini);
// 				builtin_exec(&mini);
// 				execution(&mini);
// 			}
// 			free_list(mini.start);
// 			free_cmd(&mini);
// 			free(mini.input);
// 			mini.start = NULL;
// 		}
// 	}
// 	free_env(&mini);
// 	return (0);
// }