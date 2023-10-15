#ifndef PARSING_H
# define PARSING_H

char	**ft_parse_cmd(char *cmd_str);
char	*ft_getfwd(char *str);
t_exec	*ft_parse_input(char *strcmd, char *const envp[]);

#endif
