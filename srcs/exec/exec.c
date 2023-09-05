/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:37:12 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/05 16:13:35 by hdupuy           ###   ########.fr       */
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

void	absolute_not_found(t_cmd *node)
{
	ft_printf("mini: No such file or directory: ");
	ft_printf("%s\n", node->cmd);
	free(node->cmd);
	free(node);
}

int	handle_absolute_path(t_cmd *node)
{
	if (access(node->cmd, F_OK | X_OK) == 0)
	{
		node->cmd_path = ft_strdup(node->cmd);
		return (1);
	}
	else
	{
		absolute_not_found(node);
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
			current = current->next;
		current->next = node;
	}
}

void	print_args(t_mini *mini)
{
	int		i;
	t_cmd	*current;

	i = -1;
	if (mini->cmd_tab == NULL)
		return ;
	current = mini->cmd_tab;
	while (current)
	{
		ft_printf("cmd : %s\n", current->cmd);
		ft_printf("path : %s\n", current->cmd_path);
		while (current->cmd_args && current->cmd_args[++i])
			ft_printf("args : %s\n", current->cmd_args[i]);
		ft_printf("input : %s\n", current->output_file);
		current = current->next;
		i = -1;
	}
}

t_cmd	*create_new_cmd(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (node == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->cmd = NULL;
	node->cmd_path = NULL;
	node->cmd_args = NULL;
	node->output_file = NULL;
	node->next = NULL;
	return (node);
}

// Fonction pour gérer la redirection d'entrée (<)
void	handle_input_redirection(t_cmd *cmd, const char *filename)
{
	// Enregistrez le nom du fichier d'entrée
	// cmd->cmd_path = strdup(filename);
}

// Fonction pour gérer la redirection de sortie (>)
void	handle_output_redirection(t_cmd *cmd, const char *filename)
{
	// Enregistrez le nom du fichier de sortie
	// cmd->output_file = ft_strdup(filename);
	// Utilisez t_redirection ou une structure similaire pour gérer plusieurs types de redirection
}

// Fonction pour gérer la redirection de sortie en mode ajout (>>)
void	handle_append_redirection(t_cmd *cmd, const char *filename)
{
	// Enregistrez le nom du fichier de sortie en mode ajout
	// Utilisez t_redirection ou une structure similaire pour gérer plusieurs types de redirection
}

// Fonction pour gérer le here-document (<<)
void	handle_heredoc(t_cmd *cmd, const char *content)
{
	// Enregistrez le contenu du here-document
	// Utilisez t_redirection ou une structure similaire pour gérer plusieurs types de redirection
}

// Fonction pour gérer une commande
void	handle_arg(t_cmd *cmd, const char *argument)
{
	int	num_args;

	num_args = 0;
	if (cmd->cmd_args)
	{
		while (cmd->cmd_args[num_args] != NULL)
			num_args++;
	}
	cmd->cmd_args = realloc(cmd->cmd_args, (num_args + 2) * sizeof(char *));
	if (cmd->cmd_args == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	cmd->cmd_args[num_args] = strdup(argument);
	cmd->cmd_args[num_args + 1] = NULL;
}

void	handle_cmd(t_mini *mini, t_cmd **head, t_token *start, t_cmd *node)
{
	// Enregistrez le nom de la commande
	if (!node || !start)
		return ;
	node->cmd = ft_strdup(start->str);
	if (!handle_path(mini->env, node))
	{
		return ;
	}
	handle_arg(node, start->str);
	add_cmd_node(node, head);
	return ;
}

// Fonction pour gérer un argument

void	cmd_args(t_mini *mini)
{
	t_token	*current;
	int		expecting_input;
	int		expecting_output;
	int		expecting_append;
	int		expecting_heredoc;
	int		new_cmd;
	t_cmd	*current_cmd;

	current = mini->start;
	expecting_input = 0;
	expecting_output = 0;
	expecting_append = 0;
	expecting_heredoc = 0;
	new_cmd = 0;
	current_cmd = NULL; // La commande en cours de traitement
	while (current != NULL)
	{
		// if (new_cmd == 0)
		// {
		// 	current_cmd = create_new_cmd();
		// 	new_cmd = 1;
		// }
		if (current->type == CMD)
		{
			// Créez une nouvelle structure t_cmd pour la commande actuelle
			current_cmd = create_new_cmd();
			if (expecting_input)
			{
				// Le token précédent était un opérateur de redirection (<)
				// Traitez-le comme un nom de fichier d'entrée pour la commande précédente
				handle_input_redirection(current_cmd, current->str);
				expecting_input = 0;
			}
			else if (expecting_output)
			{
				// Le token précédent était un opérateur de redirection (>)
				// Traitez-le comme un nom de fichier de sortie
				handle_output_redirection(current_cmd, current->str);
				expecting_output = 0;
			}
			else if (expecting_append)
			{
				// Le token précédent était un opérateur de redirection (>>)
				// Traitez-le comme un nom de fichier de sortie en mode ajout
				handle_append_redirection(current_cmd, current->str);
				expecting_append = 0;
			}
			else if (expecting_heredoc)
			{
				// Le token précédent était un opérateur de here-document (<<)
				// Traitez-le comme le contenu du here-document
				handle_heredoc(current_cmd, current->str);
				expecting_heredoc = 0;
			}
			else
			{
				// Traitez la commande normalement
				handle_cmd(mini, &mini->cmd_tab, current, current_cmd);
			}
		}
		else if (current->type == ARG)
		{
			if (expecting_input)
			{
				// Le token précédent était un opérateur de redirection (<)
				// Traitez-le comme un nom de fichier d'entrée pour la commande précédente
				handle_input_redirection(current_cmd, current->str);
				expecting_input = 0;
			}
			else if (expecting_output)
			{
				// Le token précédent était un opérateur de redirection (>)
				// Traitez-le comme un nom de fichier de sortie
				handle_output_redirection(current_cmd, current->str);
				expecting_output = 0;
			}
			else if (expecting_append)
			{
				// Le token précédent était un opérateur de redirection (>>)
				// Traitez-le comme un nom de fichier de sortie en mode ajout
				handle_append_redirection(current_cmd, current->str);
				expecting_append = 0;
			}
			else if (expecting_heredoc)
			{
				// Le token précédent était un opérateur de here-document (<<)
				// Traitez-le comme le contenu du here-document
				handle_heredoc(current_cmd, current->str);
				expecting_heredoc = 0;
			}
			else
			{
				// Traitez l'argument normalement
				handle_arg(current_cmd, current->str);
				new_cmd = 0;
			}
		}
		else if (current->type == INPUT)
		{
			// Marquez que nous attendons une redirection d'entrée
			expecting_input = 1;
		}
		else if (current->type == TRUNC)
		{
			// Marquez que nous attendons une redirection de sortie >
			expecting_output = 1;
		}
		else if (current->type == APPEND)
		{
			// Marquez que nous attendons une redirection de sortie >>
			expecting_append = 1;
		}
		else if (current->type == HEREDOC)
		{
			// Marquez que nous attendons un here-document <<
			expecting_heredoc = 1;
		}
		current = current->next;
	}
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
		while (current->cmd_args && current->cmd_args[i])
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
	// t_cmd *cmd;

	// cmd = NULL;
	cmd_args(mini);
	// cmd = mini->cmd_tab;
	// if (cmd && mini->is_pipe == 0)
	// {
	// 	// Exécution de la commande "ls -l"
	// 	if (fork() == 0)
	// 	{
	// 		execve(cmd->cmd_path, cmd->cmd_args, NULL);
	// 		perror("execve");
	// 		exit(EXIT_FAILURE);
	// 	}
	// }
	// wait(NULL);

	// char *const str_ls[3] = {"/usr/bin/ls", "-l", NULL}; // Commande "ls -l"

	// // Exécution de la commande inexistante "xyz123"
	// if (fork() == 0) {
	//     execve("/votre_chemin/xyz123", str_xyz, NULL);
	//     perror("execve xyz123");
	//     exit(EXIT_FAILURE);
	// }

	// // Attendre que les processus fils se terminent
	// wait(NULL);
	return (0);
}