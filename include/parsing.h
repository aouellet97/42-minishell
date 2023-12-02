#ifndef PARSING_H
# define PARSING_H

# include "execution.h"

typedef struct s_ms_token
{
	int					tk_type;
	char				*content;
	char				*raw_content;
	struct s_ms_token	*next;
}	t_ms_token;

enum tokens
{
	TK_STR,
	TK_IN_REDIR,
	TK_OUT_REDIR,
	TK_OUT_REDIR_AP,
	TK_HEREDOC,
	TK_PIPE,
	TK_NULL,
};

typedef struct s_exec_node {
	char **tab;
	char *path;
	int pfd[2];
	int prev_pipe_out;
	int input;
	int output;
	int pid;
	struct s_exec_node *next;
	int error_flag;
} t_exec_node;

/* ====== exec ?? ====== */
void		ft_execute_list(t_exec_node *head);
void		ft_set_node_pipes(t_exec_node *head);
t_exec_node	*ft_parse_input(char *strcmd,t_exec_node *node);

/* ====== Parsing ====== */
int			is_whitespace(char c);
int			ft_is_redirection(t_ms_token *tk_ptr);
int			get_char_index(char*s, char c);
t_ms_token	*ft_tokenize(char *line);
char*		get_var_string(char *var, char **env);
void		ft_check_empty_node(t_ms_token *head);

/* ====== Expansions ====== */
int			skip_single_quotes(char *str, int i);
char*		remove_quotes(char *line, int i);
char*		expand(char*line);
char*		expand_dollar_sign(char *line,int *i);
char		*expand_exit_status(char*line,int i);
#endif
