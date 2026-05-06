/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 01:54:02 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/06 19:25:39 by mabenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"

extern int			g_sig;

typedef enum s_type
{
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_PIPE,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
	TOKEN_WORD,
	TOKEN_ERROR,
}					t_type;

typedef enum s_action_type
{
	ACTION_EXEC,
	ACTION_REDIR,
}					t_action_type;

typedef struct s_exec_ctx
{
	char			**envp;
	int				fd_out;
	int				fd_in;
}					t_exec_ctx;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_pipe
{
	int				p[2];
	int				tmp;
}					t_pipe;

typedef struct s_tok
{
	t_type			type;
	char			*value;
	struct s_tok	*next;
	struct s_tok	*prev;
	int				is_exe;
	int				fd_in;
	int				fd_out;
	t_pipe			pipe;
}					t_tok;

typedef struct s_pipe_state
{
	t_tok			**pending;
	pid_t			*last;
	int				*has_exe;
	int				fd_out;
	int				fd_in;
}					t_pipe_state;

typedef struct s_vars
{
	int				read_prompt_ret;
	char			*ret;
	t_tok			*lexed;
}					t_vars;

typedef struct s_minish
{
	int					exit;
	struct sigaction	sa;
	char				**envp;
	char				**paths;
	t_tok				*tokens;
	t_env				*env;
}	t_minish;

typedef struct s_action
{
	int				fd_in;
	int				fd_out;
	t_tok			*lex;
	t_action_type	type;
	struct s_action	*next;
	struct s_action	*prev;
}					t_action;

typedef struct s_heredoc_ctx
{
	int				fd;
	char			*delim;
	size_t			dlen;
}					t_heredoc_ctx;
/* env */
char				**env_to_array(t_env *env);
t_env				*build_env(char **envp);
void				add_env(t_env **env, char *key, char *value);
void				env_unset(t_env **env, char *key);
void				print_env(t_env *env, int fd_out);
char				*get_env_val(t_env *env, char *key);
char				*get_env_val_alloc(t_env *env, char *key);
char				*get_env_value(t_env *env, char *key);
void				append_env(t_env **env, t_env *new);
t_env				*find_env(t_env *env, char *key);
char				*expand_squote(char *value, int *i);
char				*expand_dquote(char *value, int *i, t_minish *shell);
int					append_piece(char **res, char *piece);

/* lexer */
t_tok				*lexer(char *ret);
t_tok				*new_node(t_type tokens, char *value);
t_tok				*seek(t_tok *tokens);
t_tok				*jump(t_tok *tokens);
void				add_token_back(t_tok **tok, t_tok *new_element);
void				free_tokens(t_tok **tokens);
void				free_lexed(t_tok *lex);
char				*dollar(char *value, int *i, t_minish *shell);

/* redirections / pipes */
int					open_redir_fds(t_tok *lexed);
void				apply_redir_fds(t_tok *lexed);
void				close_redir_fds(t_tok *lexed);
void				open_pipes(t_tok *lexed);
void				apply_pipes(t_tok *lexed);
void				get_heredocs(t_tok *lexed);

/* builtins */
int					echo(t_tok *tokens);
int					export_one(t_minish *ev, char *arg);
int					pwd(t_tok *tokens);
int					env(t_minish *shell, t_tok *tokens);
int					export(t_minish *shell, t_tok *tokens);
int					unset(t_tok *tokens, t_minish *shell);
int					ft_exit(t_tok *tokens, t_minish *shell);
int					cd(t_tok *tokens, t_minish *shell);
char				*get_cd_path(t_tok *arg, t_minish *shell);
void				update_pwd(t_minish *shell, char *oldpwd);
char				*get_oldpwd(t_minish *shell);
/* execution */
int					run(t_tok *tokens, t_minish *shell);
int					run_all(t_minish *shell);
int					ft_read_prompt(char **ret);
pid_t				ft_exec_if_found(t_tok *lex, char **paths, t_exec_ctx *ctx);
void				parse_pipeline(t_tok *lexed, t_minish *shell);
void				expand_tokens(t_tok **tokens, t_minish *shell);
void				push_action(t_action **actions, t_action_type type,
						t_tok *lex);
void				free_argv(char **argv);
void				run_signal(t_minish *shell);
void				print_ascii_art(void);
pid_t				run_pipeline(t_tok *lexed, t_minish *shell, int piped);
pid_t				exec_token(t_tok *curr, t_minish *shell, int piped);
void				wait_children(pid_t last_pid, t_minish *shell);
int					has_pipe(t_tok *lexed);
int					validate_syntax(t_tok *lexed, t_minish *shell);
void				write_from_token(t_tok *curr, t_tok *content_tok);
char				*expand(char *value, t_minish *shell);
void				normal_copy(char *value, char **res, char *buffer, int *i);
int					run_all(t_minish *shell);

/* path search */
char				**get_paths(char **envp);
char				**get_paths_from_env(t_env *env);
char				*word_is_exe(char *word, char **paths);
char				**ft_build_exe_argv(t_tok *lex);
pid_t				exec_empty_segment(int fd_out, int fd_in);

/* lexer utils */
char				is_sep(char c);
int					skip_spaces(char *ret, int i);
int					add_word(char *ret, int i, t_tok **tokens, int start);
int					add_token(char *ret, int *i, t_tok **tokens);

/* misc */
int					show(t_env *env);
int					line_index(char *s, int key, int *i);
t_env				*create_node(char *data);
int					is_valid_identifier(const char *str);

#endif
