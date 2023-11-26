
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include "execution.h"
# include "parsing.h"
# include "libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "sys/errno.h"
# include <stdbool.h>

# include "testing.h"

# define SPLIT_SEP 29

enum sig_mode
{
	SIG_MAIN,
	SIG_CHILD
};

typedef struct s_minishell
{
	char **env;
	char *hdline;
	bool heredeoc_mode;
	int erno;
	
}	t_ms;

t_ms* get_ms(void);

typedef int (*t_builtin_ptr)(t_ms *, char **);

// =============== Signals ===============
void	ft_set_signal_actions(int mode);
void	ft_change_wspace(char *str);


// =============== Parsing ===============
char	**ft_parse_cmd(char *cmd_str);


// =============== Errors ===============
void	ft_raise_err(char *err_str, int err_nb);

// =============== Env ===============
int		replace_var(char**env, int index, char*value);
int		get_var_index(char *var, char *const envp[]);
char**	remove_var(char*var_to_remove,char**env);
char**	add_var(char*var, char**env);
char**	copy_env(char *const env[]);
char**	get_new_env(size_t size);
size_t	get_env_size(char**env);


// =============== Builtins ===============
int ft_export(t_ms*s_ms, char**cmd);
int ft_unset(t_ms *s_ms, char**cmd);
int ft_echo(t_ms*s_ms, char**cmd);
int ft_pwd(t_ms*s_ms, char**cmd);
int ft_env(t_ms*s_ms, char**cmd);
int ft_cd(t_ms*s_ms, char**cmd);

void heredoc(char*eof);

#endif