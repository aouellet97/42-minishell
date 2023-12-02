#include "minishell.h"

char** remove_var(char*var_to_remove,char**env)
{
	char **new_env;
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = get_env_size(env) - 1;
	new_env = get_new_env(len);
	if(!new_env)
		return NULL;
	while(i < len)
	{
		if(env[j] == var_to_remove)
			j++;	
		new_env[i] = env[j];
		i++;
		j++;
	}

	gc_free(var_to_remove);

	
	return new_env;

}

char** add_var(char*var, char**env) 
{
	char **new_env;
	int i;

	i = 0;
	new_env = get_new_env(get_env_size(env) + 1);
	if(!new_env)
		return NULL;
	
	
	while(env[i])
	{
		new_env[i] = env[i];
		i++;
	}

	new_env[i] = ft_strdup(var);
	if(!new_env)
		return NULL;
	

	return new_env;
}

int replace_var(char**env, int index, char*value)
{
	env[index] = ft_strdup(value);
	if(!env[index])
		return -1; 
	return 0;
}

char* get_var_string(char *var, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0 &&
			get_char_index(env[i],'=') == (int)ft_strlen(var))
			return env[i];
		i++;
	}
	return NULL;
}