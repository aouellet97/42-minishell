#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include "parsing.h"

char		*ft_get_cmd_path(char *cmd, char *const envp[]);
char		**ft_get_envpaths(char *const envp[]);
void		ft_free_tab(char **tab);
int			ft_exec_struct(t_exec *cmd, char *const envp[]);
void		ft_execute(t_exec *cmd, char *const envp[]);
// t_exec		**ft_parse_pipes(char *line, char *const envp[]);
void		ft_execute_tab(t_exec **cmd_tab, char *const envp[]);
void		ft_set_pipes(t_exec **exec_tab, int cmd_count);
t_exec_node	*ft_init_exec_list(t_ms_token *token_list, char *const envp[]);
char		*ft_strjoin_char(const char *s1, const char *s2, char c);
t_exec_node	*ft_creat_exec_node();

#endif
