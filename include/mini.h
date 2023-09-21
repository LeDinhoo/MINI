/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:38:18 by cbacquet          #+#    #+#             */
/*   Updated: 2023/09/21 19:00:25 by clement          ###   ########.fr       */
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
int					execute_cmd(t_mini *mini, t_cmd *current, int pipe_fd[2],
						int i);
int					execution(t_mini *mini);
int					ft_isalpha(char c);
int					get_count(t_replace *rep);
int					handle_absolute_path(t_cmd *node, char *str);
int					handle_path(char **env, t_cmd *node, char *str);
int					handle_redirection(t_cmd *current_cmd, t_token *current,
						t_expect *ex);
int					is_only(t_mini *mini);
int					minishell_cd(char *path);
int					wait_for_children(void);
t_cmd				*create_new_cmd(void);
t_token				*echo_build(t_token *head);
t_token				*split_string(const char *str, t_mini *mini);
void				absolute_not_found(char *str);
void				builtin_exec(t_mini *mini);
void				update_in_quotes(t_parser *parser);

// builtins.c
int					builtin_exec(t_cmd *cmd);
t_token				*echo_build(t_token *head);
char				*get_git_branch(void);
char				*get_prompt_str(void);
int					minishell_cd(char *path);
void				cd_build(t_mini *mini);
void				cmd_args(t_mini *mini);
void				find_redirection(t_token *current, t_expect *ex);
void				ft_close(int fd);
void				handle_append_redirection(t_cmd *cmd, const char *filename);
void				handle_arg(t_cmd *cmd, const char *argument);
void				handle_cmd(t_token *start, t_cmd *node);
void				handle_heredoc(t_cmd *cmd, const char *filename);
void				handle_input_redirection(t_cmd *cmd, const char *filename);
void				handle_output_redirection(t_cmd *cmd, const char *filename);
void				iterate_commands(t_mini *mini);
void				not_found(char *str);
void				pipe_redirection(t_mini *mini, t_cmd *current,
						int pipe_fd[2], int i);
void				replace_str(t_replace *rep);
void				set_last_cmd(t_mini *mini);
void				update_in_quotes(t_parser *parser);
void				redir_and_ret(t_cmd *current, int *ret, t_mini *mini);
int					update_ret(t_cmd *current, int ret);
void				handle_last_return_value(t_switch *swap, t_split *tkn);
void				handle_classic_env_value(t_switch *swap);
void				handle_single_quotes(t_token **head, t_split *tkn,
						const char *str);
void				handle_double_quotes(t_token **head, t_split *tkn,
						const char *str);
void				handle_single_quotes_content(t_split *tkn, const char *str);
void				handle_double_quotes_content(t_split *tkn, const char *str);
void				handle_less_than_operator(t_token **head, t_split *tkn,
						const char *str);
void				handle_greater_than_operator(t_token **head, t_split *tkn,
						const char *str);
void				handle_semicolon_or_pipe_operator(t_token **head,
						t_split *tkn, const char *str);
void				handle_space(t_token **head, t_split *tkn, const char *str);
void				handle_end_of_string(t_token **head, t_split *tkn,
						const char *str);
void				free_without_cmd(t_mini *mini);

// command_processing.c
void				update_token_types(t_mini *mini);
void				is_cmd(t_token *current, char **env, int i);
//srcs/buitltins/cd.c
void				cd_build(t_cmd *cmd, t_mini *mini);
void				ft_go_home(char *path, char *old_pwd);
void				ft_go_old_pwd(char *path, char *old_pwd);
void				ft_go_back_path(t_cmd *cmd, char *path, char *old_pwd);
char				**ft_add_to_env(t_mini *mini, char *str);
bool				ft_is_in_env(char *str, t_mini *mini);
void				ft_update_env(t_cmd * cmd, char *path);
void				ft_update_env(t_mini *mini, char *old_pwd);

//srcs/builtins/utils-builtin.c
void				**ft_dup_array(char **array, bool free_array, bool dup_strings);
void				ft_free_array(void **array);
size_t				*ft_lengh_array(void **array);

//srcs/buitltins/env.c
void	env(char **envp);

//srcs/buitltins/echo.c


//srcs/buitltins/exit.c


//srcs/buitltins/export.c


//srcs/buitltins/pwd.c

//srcs/buitltins/unset.c


// exec.c
int					execution(t_mini *mini);
void				free_cmd(t_mini *mini);
void				print_args(t_mini *mini);

// error_handling.c
int					pipe_error(t_token *current);
int					redirection_error(t_token *current);

// fd_handling.c
void				setup_here_doc(t_mini *mini, char *limiter);

// init.c
void				init_expect(t_expect *ex);
void				init_struct(t_mini *mini, char **envp);

// memory_management.c
void				free_all(t_mini *mini);
void				free_cmd(t_mini *mini);
void				free_env(t_mini *mini);
void				free_list(t_token *head);

// node_management.c
void				add_cmd_node(t_cmd *node, t_cmd **head);
void				add_node(t_token **head, char *str, int type);
void				add_token_to_list(t_token **head, const char *start,
						int tokenLength, t_split *tkn);

// pars_token.c
int					pars_token(t_mini *mini);
int					is_here_doc(t_token *current);
int					missing_pipe(t_mini *mini, t_token *current);
char				*here_prompt(void);
char				*pipe_prompt(void);

// path.c
void				get_path(t_mini *mini);

// print_helper.c
void				print_args(t_mini *mini);
void				print_list(t_token *head);
void				print_error(char *action);

#endif
