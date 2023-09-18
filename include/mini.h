/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:00:01 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 13:33:12 by hdupuy           ###   ########.fr       */
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

# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

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
	int				ret;
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

typedef struct s_expect
{
	int				input;
	int				output;
	int				append;
	int				heredoc;
}					t_expect;

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
	int				pid_value;
	int				ret;
	///
	char			*input;
	char			**env;
	char			**envp;
	struct s_token	*start;
	struct s_cmd	*cmd_tab;
}					t_mini;

char				*allocate_memory(t_replace *rep);
char				*find_dollar_value(char *token, int i);
char				*get_git_branch(void);
char				*get_prompt_str(t_mini *mini);
char				*here_prompt(void);
char				*pipe_prompt(void);
char				*replace_substring(char *str, char *str1, char *str2);
char				*substitute_variable_value(char *token, t_split *tkn);
int					access_path(char **env, t_cmd *node, char *str);
int					apply_append(t_cmd *current);
int					apply_heredoc(void);
int					apply_input(t_cmd *current);
int					apply_output(t_cmd *current);
int					apply_redirection(t_cmd *current);
int					cmd_numbers(t_cmd *cmd);
int					determine_token_type(const char *str);
int					error_message(char *path);
int					execute_cmd(t_mini *mini, t_cmd *current, int pipe_fd[2], int i);
int					execution(t_mini *mini);
int					ft_isalpha(char c);
int					get_count(t_replace *rep);
int					handle_absolute_path(t_cmd *node, char *str);
int					handle_path(char **env, t_cmd *node, char *str);
int					handle_redirection(t_cmd *current_cmd, t_token *current, t_expect *ex);
int					is_here_doc(t_token *current);
int					is_only(t_mini *mini);
int					is_redirection(t_token *current);
int					minishell_cd(char *path);
int					missing_pipe(t_mini *mini, t_token *current);
int					pars_token(t_mini *mini);
int					pipe_error(t_token *current);
int					redirection_error(t_token *current);
int					wait_for_children(void);
t_cmd				*create_new_cmd(void);
t_token				*echo_build(t_token *head);
t_token				*split_string(const char *str, t_mini *mini);
void				absolute_not_found(char *str);
void				add_cmd_node(t_cmd *node, t_cmd **head);
void				add_node(t_token **head, char *str, int type);
void				add_token_to_list(t_token **head, const char *start, int tokenLength, t_split *tkn);
void				builtin_exec(t_mini *mini);
void				cd_build(t_mini *mini);
void				cmd_args(t_mini *mini);
void				find_redirection(t_token *current, t_expect *ex);
void				free_all(t_mini *mini);
void				free_cmd(t_mini *mini);
void				free_env(t_mini *mini);
void				free_list(t_token *head);
void				ft_close(int fd);
void				get_path(t_mini *mini);
void				handle_append_redirection(t_cmd *cmd, const char *filename);
void				handle_arg(t_cmd *cmd, const char *argument);
void				handle_cmd(t_token *start, t_cmd *node);
void				handle_heredoc(t_cmd *cmd, const char *filename);
void				handle_input_redirection(t_cmd *cmd, const char *filename);
void				handle_output_redirection(t_cmd *cmd, const char *filename);
void				init_expect(t_expect *ex);
void				init_struct(t_mini *mini, char **envp);
void				is_cmd(t_token *current, char **env, int i);
void				iterate_commands(t_mini *mini);
void				not_found(char *str);
void				pipe_redirection(t_mini *mini, t_cmd *current, int pipe_fd[2], int i);
void				print_args(t_mini *mini);
void				print_error(char *action);
void				print_list(t_token *head);
void				replace_str(t_replace *rep);
void				set_last_cmd(t_mini *mini);
void				setup_here_doc(t_mini *mini, char *limiter);
void				update_in_quotes(t_parser *parser);
void				update_token_types(t_mini *mini);

#endif
