/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouellet <aouellet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:07:16 by aouellet          #+#    #+#             */
/*   Updated: 2023/12/04 19:07:18 by aouellet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ms	*get_ms(void)
{
	static t_ms	ms;

	return (&ms);
}

t_mblock	*garbage_collector(void)
{
	static t_mblock	head = {NULL, NULL};

	return (&head);
}
