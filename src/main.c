# include "minishell.h"

void handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * Setup terminal to prevent "^C" output on SIGINT
 **/
void setup_term(void)
{
	struct termios t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

/**
 * Handel SIGINT and ignore SIGQUIT
*/
void set_signal_actions(void)
{
	struct sigaction sa;
	sigset_t signal_set;

	setup_term();

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sigemptyset(&signal_set);
	sa.sa_mask = signal_set;

	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int main(void)
{
	char *line;

	set_signal_actions();

	while (1)
	{
		line = readline("minishell > ");
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			printf("exit");
			exit(0);
		}
	}
}