#ifndef PARSING_H
# define PARSING_H


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
	TK_PIPE,
	TK_HEREDOC
};

char		**ft_sep_tokens(char *cmd_str);
char		*ft_getfwd(char *str);
t_exec		*ft_parse_input(char *strcmd, char *const envp[]);
int			is_whitespace(char c);
char		**ft_parse_cmd(char *strcmd);
t_ms_token	*ft_tokenize_cmd(char *line, char *const envp[]);
char		*replace_vars_by_value(char *line, char *const envp[]);

#endif
