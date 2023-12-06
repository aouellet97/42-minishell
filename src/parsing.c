/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:40:49 by kmehour           #+#    #+#             */
/*   Updated: 2023/12/06 17:40:50 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	@brief Parse the raw input of a command into a t_exec structure

	@param strcmd Command in string format
	@param exec_node The node to parse into
 */
t_exec_node	*ft_parse_input(char *strcmd, t_exec_node *node)
{
	t_exec_node	*cmd;

	cmd = node;
	if (strcmd)
	{
		cmd->tab = ft_parse_cmd(strcmd);
		cmd->path = ft_get_cmd_path(cmd->tab[0], get_ms()->env);
	}
	return (cmd);
}

t_ms_token	*ft_parse_heredoc(t_ms_token *tk_ptr, t_exec_node *curr_node)
{
	if (tk_ptr->tk_type == TK_HEREDOC)
	{
		tk_ptr = tk_ptr->next;
		if (!tk_ptr)
			return (tk_ptr);
		if (curr_node->input > 2)
			close(curr_node->input);
		curr_node->input = ft_create_heredoc(tk_ptr->raw_content);
		if (curr_node->input == -1)
			curr_node->error_flag = true;
	}
	return (tk_ptr);
}

t_ms_token	*ft_parse_redirection(t_ms_token *tk_ptr, t_exec_node *curr_node)
{
	if (ft_is_redirection(tk_ptr))
	{
		if (curr_node->error_flag == false)
			ft_handle_redirections(curr_node, tk_ptr);
		tk_ptr = tk_ptr->next;
	}
	return (tk_ptr);
}

t_exec_node	*ft_parse_pipe(t_ms_token *tk_ptr, t_exec_node *curr_node,
	char **str_ptr)
{
	if (tk_ptr->tk_type == TK_PIPE)
	{
		ft_parse_input(*str_ptr, curr_node);
		*str_ptr = NULL;
		curr_node->next = ft_creat_exec_node();
		curr_node = curr_node->next;
	}
	return (curr_node);
}

/*
	@breif Create a t_exec_node linked list from the t_ms_token list
	@param head Head of the token linked list
	@return t_exec_node linked list
 */
t_exec_node	*ft_init_exec_list(t_ms_token *tk_head)
{
	t_exec_node	*head;
	t_ms_token	*tk_ptr;
	t_exec_node	*curr_node;
	char		*strcmd;

	tk_ptr = tk_head;
	curr_node = ft_creat_exec_node();
	head = curr_node;
	strcmd = NULL;
	while (tk_ptr && get_ms()->stop_hd == false)
	{
		if (tk_ptr->tk_type == TK_STR)
		{
			if (tk_ptr->content == NULL)
				tk_ptr->content = "\e";
			strcmd = ft_strjoin_char(strcmd, tk_ptr->content, 29);
		}
		curr_node = ft_parse_pipe(tk_ptr, curr_node, &strcmd);
		tk_ptr = ft_parse_heredoc(tk_ptr, curr_node);
		tk_ptr = ft_parse_redirection(tk_ptr, curr_node);
		tk_ptr = tk_ptr->next;
	}
	ft_parse_input(strcmd, curr_node);
	return (head);
}
