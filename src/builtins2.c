#include "minishell.h"

int	verify_arg_input(char *var)
{
	int	i;

	i = 0;
	if (var[0] == '=')
		return (-1);
	if (ft_isdigit(var[i]))
		return (-1);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

int	ft_tab_len(void **tab)
{
	int	count;

	count = 0;
	while (tab[count])
		count++;
	return (count);
}

/*
	@brief Checks if a string is numeric

	@returns 0 if the string is numeric, 1 otherwise
 */
int	ft_is_numeric(char *str_num)
{
	int		i;
	char	c;

	i = 0;
	while (str_num[i])
	{
		c = str_num[i];
		if ((c < '0' || c > '9') && ft_strchr("+-", c) == NULL)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_ms *s_ms, char **cmd_tab,t_exec_node *cmd_node)
{
	int	cmd_count;
	int	exit_code;

	(void) s_ms;
	(void) cmd_node;

	//printf("here %d\n",cmd_node->input);
	if(get_ms()->node_i == 1)
		printf("exit\n");
	exit_code = 0;
	cmd_count = ft_tab_len((void **)cmd_tab);
	if (cmd_count > 2)
	{
		ft_raise_err("exit", "too many arguments", 1);
		exit(1);
	}
	if (cmd_count == 2)
	{
		if (ft_is_numeric(cmd_tab[1]) != 0)
		{
			ft_raise_err("exit", "numeric argument required", 255);
			gc_free_all();
			exit(255);
		}
		exit_code = ft_atoi(cmd_tab[1]);
	}

	gc_free_all();
	exit(exit_code);
}
