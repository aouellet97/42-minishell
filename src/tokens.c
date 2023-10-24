# include "minishell.h"

// divide line into a token linkedlist


/* 
	@brief Create or append a node to a token linked list
*/
t_ms_token *ft_add_token(t_ms_token *head, char *content, char *const envp[])
{
	t_ms_token *new;
	t_ms_token *ptr;

	new = calloc(1, sizeof(t_ms_token));
	new->content = replace_vars_by_value(content, envp);
	if (head == NULL)
	{
		return new;
	}
	ptr = head;
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	ptr->next = new;
	return head;
}

t_ms_token *ft_tokenize_cmd(char *line, char *const envp[])
{
	int i;
	char **split_tab;
	t_ms_token *token_list;

	// TODO : check simple, double quote

	// split command with whitespaces
	split_tab = ft_sep_tokens(line);

	// Loopt through split_tab and create token list
	i = 0;
	token_list = NULL;
	while(split_tab[i])
	{
		// create node : node->val = from split_tab[i]
		token_list = ft_add_token(token_list, split_tab[i], envp);

		i++;
	}
	ft_free_tab(split_tab);

	return token_list;
}
