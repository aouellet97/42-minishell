#include "minishell.h"

char	**ft_parse_cmd(char *cmd_str)
{
	char **new_tab;
	int i;


	new_tab= ft_split(cmd_str, SPLIT_SEP);
	i = 0;

	while (new_tab[i])
	{
		if (new_tab[i][0] == '\e')
			new_tab[i][0] = '\0';
		i++;
	}
	return (new_tab);
}

/*
	@brief Parse the raw input of a command into a t_exec structure

	@param strcmd Command in string format
	@param exec_node The node to parse into
 */
t_exec_node	*ft_parse_input(char *strcmd, t_exec_node *node)
{
	t_exec_node	*cmd = NULL;

	cmd = node;

	cmd->tab = ft_parse_cmd(strcmd);
	cmd->path = ft_get_cmd_path(cmd->tab[0], get_ms()->env);

	return cmd;
}
void ft_handle_redirections(t_exec_node *node, t_ms_token *tk_ptr)
{
	int tk_type;
	int fd;
	char *path;

	fd = -1;
	path = tk_ptr->next->content;
	tk_type = tk_ptr->tk_type;
	if (tk_type == TK_IN_REDIR)
	{
		if (node->input > 2)
			close(node->input);
		// Check if file is readable ?
		if (access(path, R_OK) == -1)
		{
			write(2, "File not found : ", ft_strlen("File not found : "));
			write(2, path, ft_strlen(path));
			write(2, "\n", 1);
			fd = open("/dev/null", O_RDONLY);
			node->input = fd;
		}
		else
		{
			fd = open(path, O_RDONLY);
			node->input = fd;
		}
	}

	if (tk_type == TK_OUT_REDIR)
	{	
		if (node->output > 2)
			close(node->output);
		// Create file with truncation
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		//Set node->output
		node->output = fd;
	}

	if (tk_type == TK_OUT_REDIR_AP)
	{
		if (node->output > 2)
			close(node->output);
		// create or append to the file
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
		//Set node->output
		node->output = fd;
	}
}

/*
	@breif Create a t_exec_node linked list from the t_ms_token list
	@param head Head of the token linked list
	@return t_exec_node linked list
 */
t_exec_node *ft_init_exec_list(t_ms_token *tk_head)
{
	t_exec_node	*head;
	t_ms_token	*tk_ptr;
	t_exec_node	*curr_node;
	char		*strcmd;

	tk_ptr = tk_head;
	curr_node = ft_creat_exec_node();
	head = curr_node;
	strcmd = NULL;

	while(tk_ptr)
	{
		if (tk_ptr->tk_type == TK_STR)
		{
			if (tk_ptr->content == NULL)
				tk_ptr->content = "\e"; // Handles cat ""
			strcmd = ft_strjoin_char(strcmd, tk_ptr->content, 29);
		}
		if (tk_ptr->tk_type == TK_PIPE)
		{
			ft_parse_input(strcmd, curr_node);
			strcmd = NULL;
			curr_node->next = ft_creat_exec_node();
			curr_node = curr_node->next;
		}
		// if Heredoc
		if (tk_ptr->tk_type == TK_HEREDOC)
		{
			//	create heredoc file and getnextline until EOF
			tk_ptr = tk_ptr->next;
			if (!tk_ptr)
				continue ;
			if (curr_node->input > 2)
				close(curr_node->input);
			curr_node->input = ft_create_heredoc(tk_ptr->raw_content);
			// TODO: Add error if failed ?
			if (curr_node->input == -1)
				curr_node->error_flag = true;		
			
		}
		// if redirct
			// update curr_node->in/out
		if(ft_is_redirection(tk_ptr))
		{
			ft_handle_redirections(curr_node, tk_ptr);
			tk_ptr = tk_ptr->next;
		}
			tk_ptr = tk_ptr->next;
	}
	ft_parse_input(strcmd, curr_node);
	return head;
}

