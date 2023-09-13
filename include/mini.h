/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:00:01 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/13 14:03:02 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include "../utils/ft_printf/ft_printf.h"
# include "../utils/libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

// TOKEN TYPE
# define PATH_MAX 4096
# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7
# define HEREDOC 8

// ERROR
# define PIPE_ERR "Syntax error: \"|\" unexpected"
# define LINE_ERR "Syntax error: newline unexpected"

typedef struct s_switch
{
	char			*substitutedtoken;
	char			*variablename;
	char			*variablevalue;
	int				is_switch;
}					t_switch;

typedef struct s_replace
{
	char			*str;
	char			*str1;
	char			*str2;
	int				len_substr1;
	int				len_substr2;
	int				count;
	char			*resultat;
}					t_replace;

typedef struct s_split
{
	int				start;
	int				end;
	int				length;
	int				in_quotes;
	int				in_simple_quotes;
	int				tokenlength;
}					t_split;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_parser
{
	t_token			*head;
	int				start;
	size_t			end;
	int				in_quotes;
}					t_parser;

typedef struct s_redir
{
	char			*input_file;
	char			*output_file;
	char			*append_file;
	char			*heredoc_content;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			*cmd_path;
	char			**cmd_args;
	struct s_redir	redir;
	int				is_last;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_mini
{
	int				is_here_doc;
	int				here_doc_fd;
	int				nb_steps;
	int				input_fd;
	///
	char			*input;
	char			**env;
	char			**envp;
	struct s_token	*start;
	struct s_cmd	*cmd_tab;
}					t_mini;

// path.c :

void				get_path(t_mini *mini);
// init.c :

void				init_struct(t_mini *mini, char **envp);
// node_management.c :

void				add_node(t_token **head, char *str, int type);
void				free_list(t_token *head);
// token_identification.c :

int					determine_token_type(const char *str);
char				*substitute_variable_value(char *token, t_split *tkn);
void				add_token_to_list(t_token **head, const char *start,
						int tokenLength, t_split *tkn);

// command_processing.c :

void				is_cmd(t_token *current, char **env, int i);
void				update_token_types(t_mini *mini);
// memory_management.c :

void				free_env(t_mini *mini);
// print_helper.c :

void				print_list(t_token *head);

// string_split.c :

t_token				*split_string(const char *str, t_mini *mini);
void				update_in_quotes(t_parser *parser);

// builtins.c
void				builtin_exec(t_mini *mini);
t_token				*echo_build(t_token *head);
char				*get_git_branch(void);
char				*get_prompt_str(void);
int					minishell_cd(char *path);
void				cd_build(t_mini *mini);

// exec.c
int					execution(t_mini *mini);
void				free_cmd(t_mini *mini);
void				print_args(t_mini *mini);

// error_handling.c
int					pars_token(t_mini *mini);
void				print_error(char *action);
int					pipe_error(t_token *current);
int					redirection_error(t_token *current);

// fd_handling.c
void				setup_here_doc(t_mini *mini, char *limiter);

// pars_token.c
int					pars_token(t_mini *mini);
char				*pipe_prompt(void);
char				*here_prompt(void);
int					is_here_doc(t_token *current);

#endif
