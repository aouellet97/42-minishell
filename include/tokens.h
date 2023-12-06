/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:40:11 by kmehour           #+#    #+#             */
/*   Updated: 2023/12/06 17:40:12 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "minishell.h"

int		is_meta(char c);
void	ft_check_open_quotes(char *line);
int		skip_quotes(char *str, int i, char quote);
int		get_char_index(char*s, char c);

#endif