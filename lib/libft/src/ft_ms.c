#include "libft.h"


t_ms* get_ms(void)
{
	static t_ms ms;

	return &ms;
}