/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:50:39 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/16 19:25:49 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include "execution.h"
# include "parsing.h"
# include "libft.h"
# include "readline/readline.h"
# include "readline/history.h"

# include "testing.h"

# define SPLIT_SEP 29

enum sig_mode{
	SIG_MAIN,
	SIG_CHILD
};


// =============== Signals ===============
void	ft_set_signal_actions(int mode);
void	ft_change_wspace(char *str);


// =============== Parsing ===============
char	**ft_parse_cmd(char *cmd_str);


#endif