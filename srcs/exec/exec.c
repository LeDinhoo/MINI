/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:37:12 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/12 11:01:53 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	not_found(char *str)
{
	ft_printf("mini: command not found:");
	ft_printf(" %s\n", str);
	// free(node->cmd);
	// free(node);
}

void	absolute_not_found(char *str)
{
	ft_printf("mini: No such file or directory: ");
	ft_printf("%s\n", str);
	// free(node->cmd);
	// free(node);
}

int	handle_absolute_path(t_cmd *node, char *str)
{
	if (access(str, F_OK | X_OK) == 0)
	{
		node->cmd_path = ft_strdup(node->cmd);
		return (1);
	}
	else
	{
		absolute_not_found(str);
		return (0);
	}
}

int	access_path(char **env, t_cmd *node, char *str)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		tmp = str;
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
	not_found(str);
	return (0);
}

int	handle_path(char **env, t_cmd *node, char *str)
{
	if (str[0] == '/' || (str[0] == '.' && str[1] == '/'))
	{
		if (handle_absolute_path(node, str))
			return (1);
		else
			return (0);
	}
	if (access_path(env, node, str))
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

	i = 0;
	if (mini->cmd_tab == NULL)
		return ;
	current = mini->cmd_tab;
	while (current != NULL)
	{
		ft_printf("---- Command ----\ncmd : %s\n", current->cmd);
		ft_printf("path : %s\n", current->cmd_path);
		while (current->cmd_args && current->cmd_args[i])
		{
			ft_printf("args : %s\n", current->cmd_args[i]);
			i++;
		}
		ft_printf("--- Redirection ---\noutput : %s\n",
			current->redir.output_file);
		ft_printf("append : %s\n", current->redir.append_file);
		ft_printf("input : %s\n", current->redir.input_file);
		ft_printf("heredoc : %s\n\n", current->redir.heredoc_content);
		current = current->next;
		i = 0;
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
	node->is_last = 0;
	node->redir.output_file = NULL;
	node->redir.append_file = NULL;
	node->redir.input_file = NULL;
	node->redir.heredoc_content = NULL;
	node->next = NULL;
	return (node);
}

// Fonction pour gérer la redirection d'entrée (<)
void	handle_input_redirection(t_cmd *cmd, const char *filename)
{
	// Enregistrez le nom du fichier d'entrée
	cmd->redir.input_file = strdup(filename);
}

// Fonction pour gérer la redirection de sortie (>)
void	handle_output_redirection(t_cmd *cmd, const char *filename)
{
	// Enregistrez le nom du fichier de sortie
	cmd->redir.output_file = ft_strdup(filename);
	// Utilisez t_redirection ou une structure similaire pour gérer plusieurs types de redirection
}

// Fonction pour gérer la redirection de sortie en mode ajout (>>)
void	handle_append_redirection(t_cmd *cmd, const char *filename)
{
	// Enregistrez le nom du fichier de sortie en mode ajout
	cmd->redir.append_file = strdup(filename);
	// Utilisez t_redirection ou une structure similaire pour gérer plusieurs types de redirection
}

// Fonction pour gérer le here-document (<<)
void	handle_heredoc(t_cmd *cmd, const char *filename)
{
	// Enregistrez le contenu du here-document
	cmd->redir.heredoc_content = strdup(filename);
	// Utilisez t_redirection ou une structure similaire pour gérer plusieurs types de redirection
}

// Fonction pour gérer une commande
void	handle_arg(t_cmd *cmd, const char *argument)
{
	int	num_args;

	num_args = 0;
	if (!cmd)
		return ;
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
	// if (!handle_path(mini->env, node))
	// {
	//     // return ;
	// }
	handle_arg(node, start->str);
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
	current_cmd = NULL; // La commande en cours de traitement
	new_cmd = 0;
	while (current != NULL)
	{
		if (new_cmd == 0)
		{
			current_cmd = create_new_cmd();
			new_cmd = 1;
		}
		if (current->type == CMD)
		{
			// Créez une nouvelle structure t_cmd pour la commande actuelle
			// current_cmd = create_new_cmd();
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
				handle_path(mini->env, current_cmd, current->str);
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
		if (current != NULL && (current->next == NULL || current->type == PIPE))
		{
			add_cmd_node(current_cmd, &mini->cmd_tab);
			new_cmd = 0;
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
		// FREE LES REDIRECTIONS SI IL Y EN A
		current = next;
	}
	mini->cmd_tab = NULL;
}

int	cmd_numbers(t_cmd *cmd)
{
	t_cmd	*current;
	int		nb;

	current = cmd;
	nb = 0;
	while (current != NULL)
	{
		current = current->next;
		nb++;
	}
	return (nb);
}

void	wait_for_children(int nb_steps)
{
	int	i;
	int	j;

	j = nb_steps;
	i = 0;
	while (i < j)
	{
		i++;
		wait(NULL);
	}
}

int	is_only(t_mini *mini)
{
	t_cmd	*current;
	int		i;

	i = 0;
	current = mini->cmd_tab;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void	set_last_cmd(t_mini *mini)
{
	t_cmd	*current;
	t_cmd	*last;

	current = mini->cmd_tab;
	while (current)
	{
		last = current;
		current = current->next;
	}
	last->is_last = 1;
}

void	apply_redirection(t_mini *mini, t_cmd *current)
{
	int	output_fd;
	int	input_fd;
	int	append_fd;
	int	heredoc_fd;

	if (current->redir.output_file)
	{
		output_fd = open(current->redir.output_file,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd == -1)
		{
			perror("Invalid file descriptor");
			exit(EXIT_FAILURE);
		}
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	if (current->redir.append_file)
	{
		append_fd = open(current->redir.append_file,
			O_CREAT | O_RDWR | O_APPEND, 0644);
		if (append_fd == -1)
		{
			perror("Invalid file descriptor");
			exit(EXIT_FAILURE);
		}
		dup2(append_fd, STDOUT_FILENO);
		close(append_fd);
	}
	if (current->redir.input_file)
	{
		input_fd = open(current->redir.input_file, O_RDONLY);
		if (input_fd == -1)
		{
			perror("Invalid file descriptor");
			exit(EXIT_FAILURE);
		}
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (current->redir.heredoc_content)
	{
        heredoc_fd = open("/tmp/.pipex_here_doc", O_RDONLY);
        if (heredoc_fd == -1)
        {
			perror("Invalid file descriptor");
			exit(EXIT_FAILURE);
		}
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
}

void	execute_cmd(t_mini *pip, t_cmd *current, int pipe_fd[2], int i)
{
	if (current->cmd && current->is_last == 1)
		dup2(STDOUT_FILENO, STDOUT_FILENO);
	if (i != 0)
	{
		if (pip->input_fd != 0)
		{
			dup2(pip->input_fd, STDIN_FILENO);
			close(pip->input_fd);
		}
	}
	if (current->cmd && current->is_last == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (current->redir.output_file || current->redir.input_file
		|| current->redir.append_file || current->redir.heredoc_content)
	{
		apply_redirection(pip, current);
	}
	if (current->cmd)
	{
		execve(current->cmd_path, current->cmd_args, NULL);
		exit(1);
	}
	else
		exit(1);
}

void	iterate_commands(t_mini *mini)
{
	int		pipe_fd[2];
	int		i;
	t_cmd	*current;

	i = 0;
	current = mini->cmd_tab;
	mini->input_fd = 0;
	while (current)
	{
		if (current->is_last == 0)
			pipe(pipe_fd);
		if (fork() == 0)
			execute_cmd(mini, current, pipe_fd, i);
		if (i != 0)
			close(mini->input_fd);
		if (current->is_last == 0)
		{
			close(pipe_fd[1]);
			mini->input_fd = pipe_fd[0];
		}
		current = current->next;
		i++;
	}
}

int	execution(t_mini *mini)
{
	cmd_args(mini);
	mini->nb_steps = cmd_numbers(mini->cmd_tab);
	if (is_only(mini) == 0)
		return (0);
	set_last_cmd(mini);
	iterate_commands(mini);
	wait_for_children(mini->nb_steps);
	return (0);
}