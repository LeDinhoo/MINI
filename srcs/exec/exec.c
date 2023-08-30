/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:37:12 by hdupuy            #+#    #+#             */
/*   Updated: 2023/08/30 18:58:18 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	not_found(t_cmd *node)
{
	ft_printf("mini: command not found:");
	ft_printf(" %s\n", node->cmd);
	free(node->cmd);
	free(node);
}

int	handle_absolute_path(t_cmd *node)
{
	if (access(node->cmd, F_OK | X_OK) == 0)
	{
		node->cmd_path = ft_strdup(node->cmd);
		// node->cmd = ;
		return (1);
	}
	else
	{
		perror("Error");
		free(node->cmd);
		free(node);
		return (0);
	}
}

int	access_path(char **env, t_cmd *node)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		tmp = node->cmd;
		path = ft_strdup(env[i]);
		path = ft_strjoin(path, "/");
		tmp = ft_strjoin(path, tmp);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			node->cmd_path = ft_strdup(tmp);
			free(tmp);
			return (1);
		}
		i++;
		free(tmp);
	}
	not_found(node);
	return (0);
}

int	handle_path(char **env, t_cmd *node)
{
	if (node->cmd[0] == '/' || (node->cmd[0] == '.' && node->cmd[1] == '/'))
	{
		if (handle_absolute_path(node))
			return (1);
		else
			return (0);
	}
	if (access_path(env, node))
		return (1);
	else
		return (0);
}

int	args_size(t_token *current)
{
	int	i;

	i = 0;
	while (current && (current->type == ARG || current->type == CMD))
	{
		current = current->next;
		i++;
	}
	return (i);
}

int	handle_args(t_token *current, t_cmd *node)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!current)
		return (0);
	len = args_size(current);
	node->cmd_args = ft_calloc(sizeof(char *), len + 1);
	while (current && (current->type == ARG || current->type == CMD))
	{
		node->cmd_args[i] = ft_strdup(current->str);
		current = current->next;
		i++;
	}
	node->cmd_args[i] = NULL;
	return (1);
}

void	add_cmd_node(t_cmd *node, t_cmd **head)
{
	t_cmd	*current;

	if (*head == NULL)
	{
		*head = node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = node;
	}
}

int	new_cmd(t_mini *mini, t_cmd **head)
{
	t_cmd	*node;
	t_token	*token;

	token = mini->start;
	node = malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->cmd = ft_strdup(token->str);
	if (!handle_path(mini->env, node))
		return (0);
	if (!handle_args(mini->start, node))
		return (0);
	node->next = NULL;
	add_cmd_node(node, head);
	return (1);
}

void	print_args(t_mini *mini)
{
	int	i;

	i = -1;
	if (mini->cmd_tab == NULL)
		return ;
	ft_printf("cmd : %s\n", mini->cmd_tab->cmd);
	ft_printf("path : %s\n", mini->cmd_tab->cmd_path);
	while (mini->cmd_tab->cmd_args[++i])
		ft_printf("args : %s\n", mini->cmd_tab->cmd_args[i]);
}

void	cmd_args(t_mini *mini, int is_pipe)
{
	if (is_pipe == 0)
	{
		if (!new_cmd(mini, &mini->cmd_tab))
			return ;
		// while (current->next && (current->type != ARG
		// && current->type != CMD))
		// 	current = current->next;
		// while (current->next && (current->type == ARG
		// || current->type == CMD))
		// {
		// 	current = current->next;
		// 	ft_printf("%s\n", current->str);
		// }
	}
	// else
	// {
	// while (current->next && (current->type != ARG && current->type != CMD))
	// 	current = current->next;
	// ft_printf("%s\n", current->str);
	// while (current->next && (current->type == ARG || current->type == CMD))
	// {
	// 	current = current->next;
	// 	ft_printf("%s\n", current->str);
	// }
	// while (current->next && (current->type != PIPE))
	// 	current = current->next;
	// current = current->next;
	// while (current->next && (current->type == ARG || current->type == CMD))
	// {
	// 	current = current->next;
	// 	ft_printf("%s\n", current->str);
	// }
	// ft_printf("%s\n", current->str);
	// }
	// Initialiser le premier noeud;
	//  Verifier si le premier token etant CMD est valide
	//{
	//  Si Valide
	// {
	// sauvegarder le path dans *cmd_path;
	// sauvegarder le nom de la commande dans cmd;
	// }
	//
	// Else afficher cmd not found;
}

void	is_pipe(t_mini *mini)
{
	t_token	*current;
	int		is_pipe;

	is_pipe = 0;
	if (mini->start == NULL)
		return ;
	current = mini->start;
	while (current)
	{
		if (current->type == PIPE)
		{
			is_pipe = 1;
			// Variables pipe a 1 on est dans une ligne de commande pipe
		}
		current = current->next;
	}
	if (is_pipe == 1)
	{
		ft_printf("PIPE\n");
		// Lancer parsing pour plusieurs commandes
		cmd_args(mini, is_pipe);
	}
	else
	{
		ft_printf("SOLO\n");
		// Donc une seul commande
		// Lancer le parsing pour une commande
		cmd_args(mini, is_pipe);
	}
	return ;
}

void	free_cmd(t_mini *mini)
{
	int		i;
	t_cmd	*current;
	t_cmd	*next;

	current = mini->cmd_tab;
	i = 0;
	while (current)
	{
		next = current->next;
		free(current->cmd);
		free(current->cmd_path);
		while (current->cmd_args[i])
		{
			free(current->cmd_args[i]);
			i++;
		}
		free(current->cmd_args);
		i = 0;
		free(current);
		current = next;
	}
	mini->cmd_tab = NULL;
}

int	execution(t_mini *mini)
{
	is_pipe(mini);
	// char *const str_ls[3] = {"ls", "-zozio", NULL}; // Commande "ls -l"

	// // Exécution de la commande "ls -l"
	// if (fork() == 0)
	// {
	// 	execve("/usr/bin/ls", str_ls, NULL);
	// 	perror("execve ls");
	// 	exit(EXIT_FAILURE);
	// }

	// // Exécution de la commande inexistante "xyz123"
	// if (fork() == 0) {
	//     execve("/votre_chemin/xyz123", str_xyz, NULL);
	//     perror("execve xyz123");
	//     exit(EXIT_FAILURE);
	// }

	// // Attendre que les processus fils se terminent
	// wait(NULL);
	// wait(NULL);
	return (0);
}