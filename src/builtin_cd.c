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

int cd_path(t_ms *s_ms,char*path,char*pwd,char*oldpwd)
{
	if(!getcwd(oldpwd,PATH_MAX))
	{
		ft_raise_err(NULL,"getcwd error",1);
		return 1;
	}
	if(chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return 1;
	}
	if(!getcwd(pwd,PATH_MAX))
	{
		ft_raise_err(NULL, "getcwd error",1);
		return 1;
	}
	update_cwd(s_ms,pwd,oldpwd);
	return 0;
}
int ft_cd(t_ms *s_ms, char **cmd)
{
	char *path;
	char pwd[PATH_MAX];
	char oldpwd[PATH_MAX];

	path = NULL;
	if(!cmd[1] || (cmd[1][0] == '~' && !cmd[1][1]))
	{
		path = ft_getenv(s_ms->env);
		if(!path)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd("HOME not set\n", 2);
			return 1;
		}
	}
	else
		path = cmd[1];
	return cd_path(s_ms,path,pwd,oldpwd);
}
