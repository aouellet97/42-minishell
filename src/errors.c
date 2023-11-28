#include "minishell.h"

/*
	@brief Raise error

	@param err_str Error message to be printed
	@param err_nb Exit status number
*/
void	ft_raise_err(char *err_str, int err_nb)
{
	char *prefix;
	char *mod_err_str;

	prefix = "";
	// prefix = "MINISHELL ERROR - "; // Distinguish between our raised errors, to be removed !!
	mod_err_str = ft_strjoin(prefix, err_str); // DEBUG line
	// perror(mod_err_str);
	ft_putstr_fd(mod_err_str, STDERR_FILENO);
	ft_putchar_fd('\n', 2);
	gc_free_all();
	exit(err_nb);
}