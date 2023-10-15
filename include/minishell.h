/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:50:39 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/15 13:54:31 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <signal.h>

# define SPLIT_SEP 29

typedef struct s_parse {
	char **cmd_tab;
	char *outfile;
	char *infile;
} t_parse;

// =============== Signals ===============
void	ft_set_signal_actions(void);
void	ft_change_wspace(char *str);


// =============== Parsing ===============
char	**ft_parse_cmd(char *cmd_str);


#endif