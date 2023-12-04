#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include "parsing.h"

void		ft_free_tab(char **tab);
char		*ft_get_cmd_path(char *cmd, char *const envp[]);
char		**ft_get_envpaths(char *const envp[]);
char		*ft_strjoin_char(const char *s1, const char *s2, char c);
int			ft_handle_builtins(t_exec_node *cmd);
t_exec_node	*ft_creat_exec_node(void);
t_exec_node	*ft_init_exec_list(t_ms_token *head);

// Pipe and FD management
void		ft_set_node_pipes(t_exec_node *node);
int			ft_close(int fd);
int			ft_dup2(int fd, int dest);
void		ft_dup_in_out(t_exec_node *cmd);
void		ft_free_n_exit(int err_code);

#endif
