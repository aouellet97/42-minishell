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
	if(!content[0])  
		return 	TK_NULL;
	// TODO: Handle heredoc
	if (content[0] == '<' && content[1] == '<' && !content[2])
		return TK_HEREDOC;
	if (content[0] == '>' && content[1] == '>' && !content[2])
		return TK_OUT_REDIR_AP;
	// TODO: Handle redirections
	if (content[0] == '<' && !content[1])
		return TK_IN_REDIR;
	if (content[0] == '>' && !content[1])
		return TK_OUT_REDIR;

	// TODO: Handle pipes
	if (content[0] == '|' && !content[1])
		return TK_PIPE;


	return TK_STR;
}


/*
	@brief Create or append a node to a token linked list
*/
t_ms_token *ft_add_token(t_ms_token *head, char *content)
{
	t_ms_token *new_token;
	t_ms_token *ptr;

	//(void) envp;
	// Create new token
	new_token = gc_calloc(1, sizeof(t_ms_token));
	//new_token->content = ft_strdup(replace_vars_by_value(content)); //modify for it to work with $"$USER" and $?
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

int skip_quotes(char *str, int i, char quote)
{
	char *next_quote;
	int j;

	j = i;
	while (str[j])
	{
		if( str[j] == quote)
		{
			next_quote = ft_strchr(&str[j + 1], str[j]);
			if (next_quote)
				return j + (next_quote - &str[j]);
		}
		j++;
	}
	return i;
}

int is_meta(char c)
{
	return(c == '|' || c == '<' || c == '>');
}

t_ms_token *get_token(t_ms_token *head, char *content)
{
	t_ms_token *new_token;
	t_ms_token *ptr;
	char *exp_content;
	//(void) envp;
	// Create new token
	
	new_token = gc_calloc(1, sizeof(t_ms_token));
	new_token->raw_content = ft_strdup(content);
	exp_content = expand(content);
	new_token->tk_type = ft_assigne_tk_type(exp_content);
	new_token->content = remove_quotes(exp_content); //modify for it to work with $"$USER" and $? and fix garbage collector

	new_token->next = NULL;
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

t_ms_token *get_meta_token(t_ms_token*head, char*line,int *i)
{
	char*content;
	char c;
	int start;

	content = NULL;
	start = *i;
	c = line[*i];
	while(line[*i] && line[*i] == c)
		(*i)++;
	content = ft_substr(line,start, *i - start);
	if(!line[*i])
		ft_raise_err("meta at end",1);//change message
	if((ft_strlen(content) > 1 && c == '|') || (ft_strlen(content) > 2 && c != '|'))
		ft_raise_err("error meta",1); //change message
	return get_token(head,content);
}

t_ms_token *get_str_token(t_ms_token*head, char*line,int *i)
{
	char*content;

	int start;
	content = NULL;
	start = *i;

	while(line[*i] && !is_whitespace(line[*i]) && !is_meta(line[*i]))
	{
		if(line[*i] == '\'' || line[*i] == '\"')
			*i = skip_quotes(line, *i, line[*i]);
		(*i)++;
	}
	content = ft_substr(line,start, *i - start);

	return get_token(head,content);
}

t_ms_token *ft_tokenize(char *line)
{
	t_ms_token *token_list;
	int i;

	token_list = NULL;
	i = 0;
	ft_check_open_quotes(line);
	
	while(line[i]) 
	{
		if(is_whitespace(line[i]))
			i++;
		else if(is_meta(line[i]))
			token_list = get_meta_token(token_list,line,&i);
		else if(!is_whitespace(line[i]))
			token_list = get_str_token(token_list, line, &i);
	}
	
	return token_list;
}

t_ms_token *ft_tokenize_cmd(char *line)
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
		token_list = ft_add_token(token_list, split_tab[i]);
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