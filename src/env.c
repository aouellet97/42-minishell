#include "minishell.h"

char** get_new_env(size_t size)
{
	char **new_env;

	new_env = (char**)gc_calloc(sizeof(char*), (size + 1));
	if(!new_env)
		return NULL;
	
	new_env[size] = NULL;

	return new_env;
}

size_t get_env_size(char**env)
{
	size_t size;

	size = 0;
	while(env[size])
		size++;

	return size;
}

char** copy_env(char *const env[])
{
	char **new_env;
	int i;

	i = 0;
	
	if(!env[0])
		return NULL;
	new_env = get_new_env(get_env_size((char**)env));
	if(!new_env)
		return NULL;

	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if(!new_env[i])
			return NULL;
		i++;
	}
	

	return new_env;
}


int get_var_index(char *var, char *const envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0 &&
			get_char_index(envp[i],'=') == (int)ft_strlen(var))
			return i;
		i++;
	}
	
	return -1;
}


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
	//gc_free(env[index]);
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
