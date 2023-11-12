#ifndef PARSING_H
# define PARSING_H

# include "execution.h"

typedef struct s_ms_token
{
	int					tk_type;
	char				*content;
	char				value;
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

typedef struct s_exec {
	char **tab;
	char *path;
	int pfd[2];
	int input;
	int output;
	int pid;
} t_exec;

typedef struct s_exec_node {
	char **tab;
	char *path;
	int pfd[2];
	int input;
	int output;
	int pid;
	struct s_exec_node *next;
} t_exec_node;

char		**ft_sep_tokens(char *cmd_str);
char		*ft_getfwd(char *str);
int			is_whitespace(char c);
char		**ft_parse_cmd(char *strcmd);
t_ms_token	*ft_tokenize_cmd(char *line);
void		ft_execute_list(t_exec_node *head);
void		ft_set_node_pipes(t_exec_node *head);
t_exec_node	*ft_parse_input(char *strcmd);
//char*replace_vars_by_value(char *line);
int skip_single_quotes(char *str, int i);
char* expand(char*line);
char*	remove_quotes(char *line);
#endif
