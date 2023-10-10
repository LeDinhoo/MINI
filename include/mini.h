/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:00:01 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/06 11:16:11 by hdupuy           ###   ########.fr       */
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
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

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
# define EXPORT 9

# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

# define PIPE_ERR "Syntax error: \"|\" unexpected"
# define LINE_ERR "Syntax error: newline unexpected"

typedef struct s_switch
{
	char				*substitutedtoken;
	char				*variablename;
	char				*variablevalue;
	int					is_switch;
}						t_switch;

typedef struct s_replace
{
	char				*str;
	char				*str1;
	char				*str2;
	int					len_substr1;
	int					len_substr2;
	int					count;
	char				*resultat;
}						t_replace;

typedef struct s_split
{
	int					start;
	int					end;
	int					length;
	int					in_quotes;
	int					in_simple_quotes;
	int					tokenlength;
	int					equal;
	int					ret;
	char				**myenvp;
	char				**shenvp;
}						t_split;

typedef struct s_token
{
	char				*str;
	int					type;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_parser
{
	t_token				*head;
	int					start;
	size_t				end;
	int					in_quotes;
}						t_parser;

typedef struct s_redir
{
	char				*input_file;
	char				*output_file;
	char				*append_file;
	char				*heredoc_content;
}						t_redir;

typedef struct s_expect
{
	int					input;
	int					output;
	int					append;
	int					heredoc;
}						t_expect;

typedef struct s_cmd
{
	char				*cmd;
	char				*cmd_path;
	char				**cmd_args;
	struct s_redir		redir;
	int					is_last;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_sig
{
	struct sigaction	*int_prompt;
	struct sigaction	*int_exec;
	struct sigaction	*int_parent;
	struct sigaction	*here_doc;
	struct sigaction	*quit_prompt;
	struct sigaction	*quit_exec;
	struct sigaction	*quit_parent;
}						t_sig;

typedef struct s_mini
{
	int					is_here_doc;
	int					here_doc_fd;
	int					nb_steps;
	int					input_fd;
	int					pid_value;
	int					ret;
	char				*input;
	char				**path;
	char				**envp;
	char				**sh_envp;
	struct s_token		*start;
	struct s_cmd		*cmd_tab;
	t_sig				*sig;
	int					savein;
	int					saveout;
	int					saveerr;
}						t_mini;

///////////////SRCS/////////////////////////////

///////////////SRCS/PARSING/////////////////////

// srcs/parsing/command_processing.c
void					update_token_types(t_mini *mini);
void					is_cmd(t_token *current, char **env, int i);

// srcs/parsing/error_handling.c
int						pipe_error(t_token *current);
int						redirection_error(t_token *current);

// srcs/parsing/fd_handling.c
void					setup_here_doc(t_mini *mini, char *limiter);

// srcs/parsing/init.c
void					init_expect(t_expect *ex);
void					init_struct(t_mini *mini, char **envp);

// srcs/parsing/memory_management.c
void					free_all(t_mini *mini);
void					free_cmd(t_mini *mini);
void					free_env(t_mini *mini);
void					free_list(t_token *head);

// srcs/parsing/node_management.c
void					add_cmd_node(t_cmd *node, t_cmd **head);
void					add_node(t_token **head, char *str, int type);
void					add_token_to_list(t_token **head, const char *start,
							int tokenLength, t_split *tkn);

// srcs/parsing/pars_token.c
int						pars_token(t_mini *mini);
int						is_here_doc(t_token *current);
int						missing_pipe(t_mini *mini, t_token *current);
char					*here_prompt(void);
char					*pipe_prompt(void);

// srcs/parsing/path.c
void					get_path(t_mini *mini);

// srcs/parsing/print_helper.c
void					print_args(t_mini *mini);
void					print_list(t_token *head);
void					print_error(char *action);

// srcs/parsing/switch_var.c
char					*substitute_variable_value(char *token, t_split *tkn);
char					*substitute_quote(char *token, t_split *tkn);
void					handle_classic_env_value(t_switch *swap, t_split *tkn);
char					*get_env(const char *name, char **myenvp);
void					handle_last_return_value(t_switch *swap, t_split *tkn);

// srcs/parsing/token_identification.c
char					*find_dollar_value(char *token, int i);
int						var_len(char *token, int i, int var_len);
int						determine_token_type(const char *str, t_split *tkn);

// srcs/parsing/utils.c
int						get_count(t_replace *rep);
char					*allocate_memory(t_replace *rep);
void					replace_str(t_replace *rep);
char					*replace_substring(char *str, char *str1, char *str2);
void					free_without_cmd(t_mini *mini);

///////////////SRCS/PARSING/STRING_SPLIT/////////////

// srcs/parsing/string_split/split_other.c
void					handle_less_than_operator(t_token **head, t_split *tkn,
							const char *str);
void					handle_greater_than_operator(t_token **head,
							t_split *tkn, const char *str);
void					handle_semicolon_or_pipe_operator(t_token **head,
							t_split *tkn, const char *str);
void					handle_space(t_token **head, t_split *tkn,
							const char *str);
void					handle_end_of_string(t_token **head, t_split *tkn,
							const char *str);

// srcs/parsing/string_split/split_quotes.c
void					handle_single_quotes(t_token **head, t_split *tkn,
							const char *str);
void					handle_double_quotes(t_token **head, t_split *tkn,
							const char *str);
int						quote_count(const char *str, int i);
int						single_quote_count(const char *str, int i);
void					handle_single_quotes_content(t_token **head,
							t_split *tkn, const char *str);
void					handle_double_quotes_content(t_token **head,
							t_split *tkn, const char *str);

// srcs/parsing/string_split/string_split.c
t_token					*split_string(const char *str, t_mini *mini);
int						missing_quote(t_mini *mini, const char *str);
char					*quote_prompt(void);
void					process_string(const char *str, t_token **head,
							t_split *tkn);
void					handle_equal(t_token **head, t_split *tkn,
							const char *str);
void					init_split(t_split *tkn, t_mini *mini, const char *str);
void					update_in_quotes(t_parser *parser);

///////////////SRCS/EXEC/////////////////////

// srcs/exec/apply_redir.c
int						apply_output(t_cmd *current);
int						apply_append(t_cmd *current);
int						apply_input(t_cmd *current);
int						apply_heredoc(void);
int						apply_redirection(t_cmd *current);

// srcs/exec/error_ret.c
int						error_message(char *path);
int						update_ret(t_cmd *current, int ret);
void					redir_and_ret(t_cmd *current, int *ret, t_mini *mini);
int						wait_for_children(void);

// srcs/exec/exec_builtin.c
bool					is_builtin(t_cmd *current);
int						env_build(t_mini *mini);
int						exec_bin(t_cmd *current, t_mini *mini);

// srcs/exec/exec.c
int						execute_cmd(t_mini *mini, t_cmd *current,
							int pipe_fd[2], int i);
void					find_redirection(t_token *current, t_expect *ex);
void					pipe_redirection(t_mini *mini, t_cmd *current,
							int pipe_fd[2], int i);
int						one_command(t_mini *mini, t_cmd *current,
							int pipe_fd[2], int i);
void					iterate_commands(t_mini *mini);
int						execution(t_mini *mini);

// srcs/exec/handle_cmd.c
t_cmd					*create_new_cmd(void);
void					handle_arg(t_cmd *cmd, const char *argument);
void					handle_cmd(t_token *start, t_cmd *node);
void					setup_command(t_mini *mini, t_token *current,
							t_cmd *current_cmd, t_expect *ex);
void					cmd_args(t_mini *mini);

// srcs/exec/handle_path.c
void					not_found(char *str);
void					absolute_not_found(char *str);
int						handle_absolute_path(t_cmd *node, char *str);
int						access_path(char **env, t_cmd *node, char *str);
int						handle_path(char **env, t_cmd *node, char *str);

// srcs/exec/handle_redir.c
void					handle_input_redirection(t_cmd *cmd,
							const char *filename);
void					handle_output_redirection(t_cmd *cmd,
							const char *filename);
void					handle_append_redirection(t_cmd *cmd,
							const char *filename);
void					handle_heredoc(t_cmd *cmd, const char *filename);
int						handle_redirection(t_cmd *current_cmd, t_token *current,
							t_expect *ex);

// srcs/exec/utils.c
int						is_only(t_mini *mini);
int						cmd_numbers(t_cmd *cmd);
void					set_last_cmd(t_mini *mini);
void					ft_close(int fd);
int						ft_isalpha(char c);

///////////////SRCS/BUILTINS/////////////////////
// srcs/builtins/cd.c
char					*get_prompt_str(t_mini *mini);
int						cd_build(t_cmd *current, t_mini *mini);
int						ft_go_home(char *path, t_mini *mini, char *old_pwd);
int						ft_go_old_pwd(char *path, t_mini *mini, char *old_pwd);
bool					ft_is_in_env(char *str, t_mini *mini);
bool					only_key_already_in_env(char *str, t_mini *mini);
bool					check_for_equal(const char *str);
char					**ft_add_to_env(t_mini *mini, char *str);
int						ft_update_env(t_mini *mini, char *old_pwd);

// srcs/builtins/echo.c
int						echo_build(t_cmd *current);

// srcs/builtins/exit.c
int					exit_build(t_cmd *current, t_mini *mini);
int						get_return_value(char **argv, bool *is_error,
							t_mini *mini);

// srcs/builtins/export.c
char					*find_var_name(char *str);
void					add_var_to_env(t_mini *mini, char *str);
void					modify_var_value(t_mini *mini, char *str,
							char *var_name);
char					*get_var_str(char **envp, char *str);
int						export_build(t_cmd *current, t_mini *mini);

// srcs/builtins/pwd.c
int						pwd_build(void);

// srcs/builtins/unset.c
void					free_envp(char **envp);
char					**init_new_envp(char **myenvp);
int						unset_build(t_cmd *current, t_mini *mini);

// srcs/builtins/utils.c
size_t					ft_lengh_array(char **array);
void					ft_free_array(char **array);

// main.c
void					print_env(char **myenvp);

///////////////////SRCS/SIGNALS//////////////////////////

// srcs/signals/handle_signals.c
void					ft_init_quit_handle(t_sig *sig);
void					ft_handle_signal(int sig_prompt);
void					ft_handle_signal_heredoc(int sig_heredoc);
void					ft_set_signals_handle(t_sig *sig);

// srcs/signals/init_signals.c
void					ft_init_signals(t_sig *sig);
void					ft_check_malloc(t_sig *sig);
void					ft_sig_quit_parent(int sig);

// srcs/signals/free_signals.c
void					free_signals(t_mini *mini);

#endif

// char					*get_git_branch(void);
// int						minishell_cd(char *path, t_mini *mini);
//
// void					builtin_exec(t_mini *mini);
//
// void					update_in_quotes(t_parser *parser);
// bool					is_not_fork(t_cmd *current);
