#include "minishell.h"

t_ms_token *ft_tokenize(char *line);

char** copy_env(char *const env[]) //delete
{
	char**new_env;
	int i;

	i = 0;
	while(env[i])
		i++;
	new_env = (char**)gc_calloc(sizeof(char*), i + 1);
	new_env[i] = NULL;

	i = 0;
	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	return new_env;
}

void print_tokens(t_ms_token*token_list,char*line)
{
	int i;

	i = 1;
	if(token_list)
		printf("\n\033[0;31m%s\n",line);
	while(token_list)
	{
		printf("\033[0;33m\n====================\n\033[0;37m");
		printf("\033[0;32mToken\033[0;34m %i\n", i);
		printf("\033[0;32mcontent:\033[0;34m %s\n",token_list->content);
		printf("\033[0;33m====================\n\033[0;37m");
		i++;
		token_list = token_list->next;

	}
}



int	main(int argc, char **argv, char *const envp[])
{
	char	*line;
	(void)	argc;
	(void)	argv;
	//t_exec_node *exec_list;

	ft_set_signal_actions(SIG_MAIN);
	get_ms()->env = copy_env(envp); //replace with other copy env fucntion
	
	// while(*(get_ms()->env))
	// {
	// 	printf("%s\n",*(get_ms()->env));
	// 	get_ms()->env++;
	// }

	
	while (1)
	{
		//	Readline
		line = readline("minishell > ");

		//	Check exit conditions
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			printf("exit\n");
			gc_free_all();
			exit(0);
		}

		//	Append to history
		if (*line)
		{
			// Add modified line to history
			add_history(line);

			// Parse Raw input
			// Create tokens from raw line
			t_ms_token *token_list = ft_tokenize(line);
			print_tokens(token_list,line);
			// Create t_exec_node list from tokens
			//exec_list = ft_init_exec_list(token_list);

			//	Execute Command(s)
		//	ft_execute_list(exec_list);
			// (void) exec_list;

		}
		free(line);
	}
}
