
#ifndef MS_H
# define MS_H

# include "stdbool.h"

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

}	t_ms;

t_ms* get_ms(void);

#endif
