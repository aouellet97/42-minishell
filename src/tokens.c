# include "minishell.h"

// divide line into a token linkedlist

t_ms_token *ft_tokenize_cmd(char *line)
{
	int l;
	int r;

	l = 0;
	r = 0;
	while (line[l])
	{
		while (line[r] && !is_whitespace(line[r]))
		{
			printf("%c", line[r]);
			r++;
		}
		while (line[r] && is_whitespace(line[r]))
		{
			r++;
		}
		printf("\n");
		l = r;
	}
	return NULL;
}