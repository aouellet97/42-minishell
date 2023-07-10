# include "minishell.h"

int main(void)
{
	ft_putstr_fd("Hello MiniShell !!\n", STDIN_FILENO);
	while (1)
	{
		readline("minishell > ");
	}
	
}