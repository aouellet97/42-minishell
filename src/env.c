#include "minishell.h"

char	**get_new_env(size_t size)
{
	char	**new_env;

	new_env = (char **) gc_calloc(sizeof(char *), (size + 1));
	if (!new_env)
		return (NULL);
	new_env[size] = NULL;
	return (new_env);
}

size_t	get_env_size(char **env)
{
	size_t	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

char	**copy_env(char *const env[])
{
	char	**new_env;
	int		i;

	i = 0;
	if (!env[0])
		return (NULL);
	new_env = get_new_env(get_env_size((char **)env));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (NULL);
		i++;
	}
	return (new_env);
}

int	get_var_index(char *var, char *const envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0 
			&& get_char_index(envp[i], '=') == (int)ft_strlen(var))
			return (i);
		i++;
	}
	return (-1);
}
