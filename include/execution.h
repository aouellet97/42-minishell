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
// t_exec		**ft_parse_pipes(char *line, char *const envp[]);
t_exec_node *ft_init_exec_list(t_ms_token *head);
char		*ft_strjoin_char(const char *s1, const char *s2, char c);
t_exec_node	*ft_creat_exec_node();
int			ft_handle_builtins(t_exec_node *cmd);
int		ft_close(int fd);
int		ft_dup2(int fd, int dest);


#endif
