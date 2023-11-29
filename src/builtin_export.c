#include "minishell.h"

int verify_arg_input(char*var) 
{
	int i;

	i = 0;
	if(var[0] == '=' && ft_strlen(var) == 1)
		return -1;
	if(ft_isdigit(var[i]))
		return -1;
	while(var[i] && var[i] != '=')
	{
		if(!ft_isalnum(var[i]) && var[i] != '_')
			return -1;
		i++;
	}

	return 0;
}

void ascii_sort(char**env, size_t len)
{
	size_t i;
	size_t j;
	char *temp;

	i = 0;
    j = 0;
	temp = NULL;
	while(j < len - 1)
	{
		while(i < len - 1)
		{
			if(strcmp(env[i],env[i + 1]) > 0)
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
void print_line(char*s)
{
	int i;

	i = 0;
	write(1,"=\"",2);

	while(s[i])
	{
		if(s[i] == '\"')
			write(1,"\\",1);
		write(1,&s[i],1);
		i++;
	}

	write(1,"\"\n",2);

}

void print_sorted_env(char**env)
{
	int i;
	int j;
	char **env_cp;

	i = 0;
    j = 0;
	
	env_cp = copy_env(env);
	if(!env_cp)
		return ;
	ascii_sort(env_cp,get_env_size(env_cp));	
	while(env_cp[i])
	{
		//what about the _= variable? include it or not?
		ft_putstr_fd("declare -x ",1);
        while(env_cp[i][j] != '=')
        {
            write(1,&env_cp[i][j],1);
            j++;
        }
        print_line(env_cp[i] + get_char_index(env_cp[i],'=') + 1);
        j = 0;
		i++;	
	}
}

int ft_export(t_ms*s_ms, char**cmd)
{
	int i;
	int index;
	char* var;
	int result;

	result = 0;
	var = NULL;
	i = 1;
	index = 0;

	if(!cmd[i])
		print_sorted_env(s_ms->env);
	while(cmd[i])
	{
		if(verify_arg_input(cmd[i]) != 0)
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			result = 1;
		}
		else if(get_char_index(cmd[i],'=') != -1)
		{
			var = ft_substr(cmd[i],0,get_char_index(cmd[i],'='));
			if(!var)
				return 1; //replace with error function
			index = get_var_index(var,s_ms->env);
			if(index != -1)
				replace_var(s_ms->env,index,cmd[i]);
			else
				s_ms->env = add_var(cmd[i],s_ms->env);
			
		}
		i++;
	}
	return result;
} 