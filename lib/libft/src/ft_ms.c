#include "libft.h"

t_ms	*get_ms(void)
{
	static t_ms	ms;

	return (&ms);
}

t_mblock	*garbage_collector(void)
{
	static t_mblock	head = {NULL, NULL};

	return (&head);
}
