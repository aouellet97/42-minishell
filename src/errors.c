#include "minishell.h"

/*
	@brief Raise error

	@param err_str Error message to be printed
	@param err_nb Exit status number
*/
void	ft_raise_err(char *err_str, int err_nb)
{
	char *mod_err_str;

	// TODO : add free gc function

	// Distinguish between our raised errors, to be removed !!
	mod_err_str = ft_strjoin("MINISHELL ERROR - ", err_str); // DEBUG line
	perror(mod_err_str);
	gc_free_all();
	exit(err_nb);
}