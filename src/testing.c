
#include "minishell.h"



void test_parsing(char *line){
	ft_change_wspace(line);
	char **list = ft_split(line, SPLIT_SEP);
	ft_print_tab(list);
}

void ft_print_tab(char **list)
{
	int i = 0;

	printf("\n\n\t========= TABLE =========\n");
	while(list[i])
	{
		printf("\t- %s\n", list[i]);
		i++;
	}
	printf("\n\t=========================\n\n");
}

void ft_print_exec_struct(t_exec *cmd)
{

	printf("\
	============ Command ============\n\
	\tInput : %i\n\
	\tOutput : %i\n\
	\tPath : %s\n\
	=================================\n\
	", cmd->input, cmd->output, cmd->path);

	ft_print_tab(cmd->tab);
}


void ft_print_exec_tab(t_exec **tab)
{
	int i = 0;

	printf("\n\n\t========= TABLE =========\n");
	while(tab[i])
	{
		ft_print_tab(tab[i]->tab);
		printf("%s\n", tab[i]->path);
		i++;
	}
	printf("\n\t=========================\n\n");
}

void ft_print_tokens(t_ms_token *head)
{
	int count;
	printf("============== Tokens ==============\n");

	count = 0;
	while(head)
	{
		printf(
			"\tToken #%i\n\tcontent : %s\n\ttoken type : %i\n\n"
			, count, head->content, head->tk_type
		);
		head = head->next;
		count++;
	}
}

void ft_print_exec_nodes(t_exec_node *head)
{
	int count;
	printf("============== Exec nodes ==============\n");

	count = 0;
	while(head)
	{
		printf(
			"\tNode #%i\n\tPath : %s\n\tinput: %i\n\toutput: %i\n"
			, count, head->path, head->input, head->output
		);
		ft_print_tab(head->tab);
		printf("-------------------------\n\n");
		head = head->next;
		count++;
	}
}






