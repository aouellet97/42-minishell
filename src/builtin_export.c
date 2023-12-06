/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:40:21 by kmehour           #+#    #+#             */
/*   Updated: 2023/12/06 17:41:01 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ascii_sort(char **env, size_t len)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	temp = NULL;
	while (j < len - 1)
	{
		while (i < len - 1)
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
			}
			i++;
		}
		i = 0;
		j++;
	}
}

void	print_line(char *s)
{
	int	i;

	i = 0;
	write(1, "=\"", 2);
	while (s[i])
	{
		if (s[i] == '\"')
			write(1, "\\", 1);
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\"\n", 2);
}

void	print_sorted_env(char **env)
{
	int		i;
	int		j;
	char	**env_cp;

	i = 0;
	j = 0;
	env_cp = copy_env(env);
	ascii_sort(env_cp, get_env_size(env_cp));
	while (env_cp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		while (env_cp[i][j] != '=')
		{
			write(1, &env_cp[i][j], 1);
			j++;
		}
		print_line(env_cp[i] + get_char_index(env_cp[i], '=') + 1);
		j = 0;
		i++;
	}
}

int	export_loop(char **cmd, int i, char *var, int index)
{
	int		result;
	char	**env;

	env = NULL;
	result = 0;
	if (verify_arg_input(cmd[i]) != 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmd[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		result = 1;
	}
	else if (get_char_index(cmd[i], '=') != -1)
	{
		var = ft_substr(cmd[i], 0, get_char_index(cmd[i], '='));
		index = get_var_index(var, get_ms()->env);
		if (index != -1)
			replace_var(get_ms()->env, index, cmd[i]);
		else
		{
			env = add_var(cmd[i], get_ms()->env);
			get_ms()->env = env;
		}
	}
	return (result);
}

int	ft_export(t_ms*s_ms, char **cmd, t_exec_node *cmd_node)
{
	int		i;
	int		index;
	char	*var;
	int		result;

	(void)cmd_node;
	result = 0;
	var = NULL;
	i = 1;
	index = 0;
	if (!cmd[i])
		print_sorted_env(s_ms->env);
	while (cmd[i])
	{
		result += export_loop(cmd, i, var, index);
		i++;
	}
	if (result > 0)
		return (1);
	return (0);
}
