#include "minishell.h"

int	main(int argc, char **argv, char *const envp[])
{
	char	**line;
	(void)	argc;
	(void)	argv;
	(void)	envp;
	// t_exec	**exec_tab = NULL;

	line = ft_split(NULL, ' ');


	for (int i = 0; line && line[i]; i++)
		printf("%s\n", line[i]);

	gc_free_all();
	
}
