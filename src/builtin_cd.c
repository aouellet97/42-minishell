#include "minishell.h"

void update_cwd(t_ms*s_ms,char*path,char*old_path)
{
	char *var;
	int index;

	
	var = ft_strjoin("PWD=",path); 
	index = get_var_index("PWD",s_ms->env);
	if(index != -1)
		replace_var(s_ms->env,index,var);

	var = ft_strjoin("OLDPWD=",old_path); 
	index = get_var_index("OLDPWD",s_ms->env);
	if(index != -1)
		replace_var(s_ms->env,index,var);

}

char* ft_getenv(char**env)
{
	char *path;

	path = get_var_string("HOME",env);
	if(path)
	{
		return (path + get_char_index(path,'=') + 1);
	}
	return NULL;
}

int ft_cd(t_ms *s_ms, char **cmd) //deal with cd - ?
{
	char *path;
	char pwd[PATH_MAX];
	char oldpwd[PATH_MAX];


	// TODO : cd into first argument, no errors
	path = NULL;
	if(cmd[1] && cmd[2])
		return 1;
	if(!cmd[1] || (cmd[1][0] == '~' && !cmd[1][1]))
	{
		path = ft_getenv(s_ms->env);
		if(!path)
		{
			printf("cd: HOME not set\n");
			return 1;
		}
	}
	else
		path = cmd[1];
	if(!getcwd(oldpwd,PATH_MAX))
		return -1;
	if(chdir(path) != 0)
	{
		ft_putstr_fd("No such file or directory", 2);
		return 1;
	}
	if(!getcwd(pwd,PATH_MAX))
		return -1;
	update_cwd(s_ms,pwd,oldpwd);
	return 0;
}