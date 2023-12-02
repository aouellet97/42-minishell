#include "minishell.h"

/*
	@brief Raise error

	@param err_str Error message to be printed
	@param err_nb Exit status number
*/
void	ft_raise_err(char *prefix, char *err_str, int err_code)
{
	if (get_ms()->found_error)
		return ;

	get_ms()->found_error = true;
	get_ms()->ms_errno = err_code;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (prefix)
	{
		ft_putstr_fd(prefix, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(err_str, STDERR_FILENO);

	if (err_code == 258)
	{
		get_ms()->reset_loop_flag = true;
		if (get_ms()->last_valid_tk)
		{
			ft_putstr_fd(" `",STDERR_FILENO);
			ft_putstr_fd(get_ms()->last_valid_tk ,STDERR_FILENO);
			ft_putstr_fd("'",STDERR_FILENO);
		}
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}
