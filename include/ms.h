/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:40:04 by kmehour           #+#    #+#             */
/*   Updated: 2023/12/06 17:40:05 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

# include "stdbool.h"

typedef struct s_lst
{
	int				value;
	struct s_lst	*next;
}	t_lst;

typedef struct s_minishell
{
	char	**env;
	char	*hdline;
	char	*hd_filename;
	int		hd_fd;
	bool	heredeoc_mode;
	int		ms_errno;
	bool	stop_hd;
	char	*line;
	bool	reset_loop_flag;
	bool	found_error;
	char	*last_valid_tk;
	char	**rl_env;
	int		node_i;
	t_lst	*fd_list;
}	t_ms;

t_ms	*get_ms(void);

#endif
