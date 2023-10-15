#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"


char	*ft_get_cmd_path(char *cmd, char *const envp[]);
char	**ft_get_envpaths(char *const envp[]);
void	ft_free_tab(char **tab);


#endif