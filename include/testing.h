/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:40:09 by kmehour           #+#    #+#             */
/*   Updated: 2023/12/06 17:40:10 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTING_H
# define TESTING_H

# include "minishell.h"
# include "libft.h"
# include <stdio.h>
# include <unistd.h>

# define COLOR_RED "\033[0;31m"
# define COLOR_BLUE "\033[0;34m"
# define COLOR_GREEN "\033[0;32m"
# define COLOR_YELLOW "\033[0;33m"
# define COLOR_RESET "\033[0m"

void	ft_print_tab(char **list);

// TOKENS
void	ft_print_tokens(t_ms_token *head);
void	print_tokens(t_ms_token*token_list, char*line);

// exec list
void	ft_print_exec_nodes(t_exec_node *head);
void	ft_print_exec_node(t_exec_node *head);

#endif