/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:50:37 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/16 19:50:35 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	
		ft_putchar_fd('\0', STDOUT_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * Setup terminal to prevent "^C" output on SIGINT
 **/
void	ft_setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

/**
 * Handel SIGINT and ignore SIGQUIT
*/
void	ft_set_signal_actions(int mode)
{

	if (mode == SIG_MAIN)
	{
		// ft_setup_term();
		signal(SIGINT, ft_handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}

	if (mode == SIG_CHILD)
	{
		signal(SIGINT, SIG_IGN);
	}
}
