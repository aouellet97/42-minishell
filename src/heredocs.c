#include "minishell.h"


char* heredoc_expand(char*line)
{
	char *gc_line;
	int i;

	i = 0;
	gc_line = ft_strdup(line);
	free(line);
	while(gc_line[i])
	{
		if(gc_line[i] == '$' && gc_line[i + 1] == '?')
			gc_line = expand_exit_status(gc_line,i);
		if(gc_line[i] == '$')
			gc_line = expand_dollar_sign(gc_line,&i);
		i++;
	}

	return gc_line;
}

char* get_file_name(void)
{
	static int eredoc_i = 0;
	char *file_name;
	char *n;

	n = ft_itoa(eredoc_i);
	file_name = ft_strjoin("/tmp/heredoc_file-",n);
	gc_free(n);

	eredoc_i++;

	return file_name;
}

void sigint_handle(int sig)
{
	if(sig ==  SIGINT)
	{
		write(1,">\n",2);
		if(get_ms()->hdline)
		{
			free(get_ms()->hdline);
			get_ms()->hdline = NULL;
		}
		gc_free_all();
		//clear heredoc file
		exit(0);
	}

}

void heredoc(char*eof) // deal with them before expand and quote removing <-----------
{
	char *filename;
	char *line;
	bool expansion;
	int fd;
	int id;

	fd = 0;
	id = 0;
	line = NULL;
	expansion = false;

	if(get_char_index(eof,'\'') == -1 && get_char_index(eof,'\"') == -1 )
		expansion = true;

	eof = remove_quotes(eof);
	if(!eof)
		eof = "\0";

	filename = get_file_name();
	fd = open(filename,  O_WRONLY | O_CREAT | O_TRUNC, 0777); 
	if(!fd)
		return ;//exit program
	
	get_ms()->heredeoc_mode = true;
	id = fork();
	if(id == 0)
	{
		signal(SIGINT,sigint_handle);
		while(1)
		{
			get_ms()->hdline = readline("> ");
		
			if(!get_ms()->hdline || (ft_strcmp(get_ms()->hdline,eof) == 0 && 
				(ft_strlen(get_ms()->hdline) == ft_strlen(eof))))
				break ; 
	
			if(expansion == true)
			{
				get_ms()->hdline= heredoc_expand(get_ms()->hdline); 
				gc_detach(get_ms()->hdline);
			}
			write(fd,get_ms()->hdline,(int)ft_strlen(get_ms()->hdline));
			write(fd,"\n",1);
			if(get_ms()->hdline)
				free(get_ms()->hdline);
		}
		if(get_ms()->hdline)
			free(get_ms()->hdline);
		gc_free_all();
		exit(0);
	}
	waitpid(id,NULL,0);
	get_ms()->heredeoc_mode = false;


} //keep the fds open and on the minishell struct for gnl


