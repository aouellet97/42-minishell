#ifndef PARSING_H
# define PARSING_H


typedef struct s_ms_token
{

}	t_ms_token;

enum tokens
{
	TK_STR,
	TK_IN_REDIR,
	TK_OUT_REDIR,
	TK_PIPE,
	TK_HEREDOC
};

char	**ft_parse_cmd(char *cmd_str);
char	*ft_getfwd(char *str);
t_exec	*ft_parse_input(char *strcmd, char *const envp[]);

#endif
