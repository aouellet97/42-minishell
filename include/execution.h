#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_exec {
	char **tab;
	char *path;
	int outfile;
	int infile;
} t_exec;


char	*ft_get_cmd_path(char *cmd, char *const envp[]);
char	**ft_get_envpaths(char *const envp[]);
void	ft_free_tab(char **tab);
int		ft_exec_struct(t_exec *cmd, char *const envp[]);
void	ft_execute(t_exec *cmd, char *const envp[]);
t_exec	**ft_parse_pipes(char *line, char *const envp[]);


#endif
