#include "minishell.h"

//------------------------------------------------------

int ft_unset(t_ms *s_ms, char**cmd)
{
	char*var_string;
	int i;

	var_string = NULL;
	i = 1;
	while(cmd[i])
	{
		var_string = get_var_string(cmd[i],s_ms->env);
		if(var_string)
			s_ms->env = remove_var(var_string,s_ms->env);
		i++;
	}
	return 0;
}


//------------------------------------------------------

int ft_pwd(t_ms *s_ms, char **cmd)
{
	char wd[PATH_MAX];

	(void) s_ms;
	(void) cmd;

	if(getcwd(wd,PATH_MAX))
	{
		printf("%s\n",wd);
		return 0;
	}

	return 1; //error function here
}

//------------------------------------------------------

int ft_env(t_ms*s_ms, char **cmd)
{
	int i;

	(void) cmd;
	i = 0;
    while(s_ms->env[i])
    {
        printf("%s\n",s_ms->env[i]);
        i++;
    }
	return 0;
}


//------------------------------------------------------

int n_flag_check(char *cmd)
{
	int i;

	i = 1;
	if(cmd[0] != '-' || cmd[1] != 'n')
		return -1;
	while(cmd[i])
	{
		if(cmd[i] != 'n')
			return -1;
		i++;
	}
	return 1;
}

int ft_echo(t_ms *s_ms, char**cmd)
{
	int i;
	int n;

	(void) s_ms;

	i = 1;
	n = 0;
	while(cmd[i] && n_flag_check(cmd[i]) == 1)
	{
		n = 1;
		i++;
	}
	while(cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO); // TODO: Change with ft_putstr_fd
		if(cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if(n == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return 0;

}

//------------------------------------------------------

int	ft_tab_len(void **tab)
{
	int count;

	count = 0;
	while(tab[count])
		count++;
	return (count);
}

/*
	@brief Checks if a string is numeric

	@returns 0 if the string is numeric, 1 otherwise
 */
int ft_is_numeric(char *str_num)
{
	int i;
	char c;

	i = 0;
	while (str_num[i])
	{
		c = str_num[i];
		if ((c < '0' || c > '9') &&
			ft_strchr("+-", c) == NULL)
		{
			return 1;
		}
		i++;
	}
	return 0;
}

int	ft_exit(t_ms*s_ms, char**cmd_tab)
{
	int cmd_count;
	int exit_code;

	(void) s_ms;
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
			exit(255);
		}
		exit_code = ft_atoi(cmd_tab[1]);
	}
	exit(exit_code);
}