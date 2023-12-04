#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include "execution.h"
# include "parsing.h"
# include "tokens.h"
# include "libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "sys/errno.h"
# include "testing.h"
# include "ms.h"

# define SPLIT_SEP 29

enum	e_sig_mode
{
	SIG_MAIN,
	SIG_CHILD
};

typedef int	(*t_builtin_ptr)(t_ms *, char **);

// =============== Signals ===============
void	ft_set_signal_actions(int mode);
void	ft_change_wspace(char *str);
void	sigint_handle(int sig);

// =============== Parsing ===============
char	**ft_parse_cmd(char *cmd_str);
int		ft_assigne_tk_type(char *content);

// =============== Errors ===============
void	ft_raise_err(char *prefix, char *err_str, int err_code);

// =============== Env ===============
int		replace_var(char**env, int index, char*value);
int		get_var_index(char *var, char *const envp[]);
char	**remove_var(char*var_to_remove, char**env);
char	**add_var(char*var, char**env);
char	**copy_env(char *const env[]);
char	**get_new_env(size_t size);
size_t	get_env_size(char**env);

// =============== Builtins ===============
char	*expand_exit_status(char*line, int i);
int		ft_export(t_ms*s_ms, char**cmd);
int		ft_unset(t_ms *s_ms, char**cmd);
int		ft_echo(t_ms*s_ms, char**cmd);
int		ft_exit(t_ms*s_ms, char**cmd);
int		ft_pwd(t_ms*s_ms, char**cmd);
int		ft_env(t_ms*s_ms, char**cmd);
int		ft_cd(t_ms*s_ms, char**cmd);
int		verify_arg_input(char*var);

int		ft_create_heredoc(char*eof);
char	*get_new_line(char*line, int start, int end, char*var_string);

#endif