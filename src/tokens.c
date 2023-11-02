# include "minishell.h"

// divide line into a token linkedlist

void ft_check_open_quotes(char *line)
{
	int i;
	char *ptr;


	i = 0;
	while(line[i])
	{
		if( line[i] == '"' || line[i] == '\'')
		{
			ptr = ft_strchr(&line[i + 1], line[i]);
			if (!ptr)
				ft_raise_err("unclosed quotes", 99);
			i += ptr - &line[i];
		}

		i++;
	}
}

/*
	@brief Assigns the token type according based on the content
*/
int ft_assigne_tk_type(char *content)
{
	// TODO: Handle strings

	// TODO: Handle heredoc

	// TODO: Handle redirections
	if (content[0] == '<')
		return TK_IN_REDIR;
	if (content[0] == '>')
		return TK_OUT_REDIR;

	// TODO: Handle pipes
	if (content[0] == '|')
		return TK_PIPE;


	return TK_STR;
}


/*
	@brief Create or append a node to a token linked list
*/
t_ms_token *ft_add_token(t_ms_token *head, char *content, char *const envp[])
{
	t_ms_token *new_token;
	t_ms_token *ptr;

	(void) envp;
	// Create new token
	new_token = ft_calloc(1, sizeof(t_ms_token));
	new_token->content = ft_strdup(replace_vars_by_value(content, envp));
	new_token->tk_type = ft_assigne_tk_type(content);

	if (head == NULL)
	{
		return new_token;
	}
	ptr = head;
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	ptr->next = new_token;
	return head;
}

t_ms_token *ft_tokenize_cmd(char *line, char *const envp[])
{
	int i;
	char **split_tab;
	t_ms_token *token_list;

	// TODO : check simple, double quote
	ft_check_open_quotes(line);
	// split command with whitespaces
	// TODO: make split work for -> echo hello ""|""wc -c
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

// TODO: Add memory deallocation function
/*
	void free_ms_tokens(t_ms_token* head){
		t_ms_token *ptr;
		ptr = head;

		while (ptr)
		{
			free(ptr.content);
		}
	}
*/