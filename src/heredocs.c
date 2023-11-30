#include "minishell.h"


void heredoc_expand(char*line)
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
	get_ms()->hdline = gc_line;
	gc_detach(get_ms()->hdline);

}

int open_heredoc_file(void)
{
	static int heredoc_i = 0;
	char *file_name;
	char *n;

	n = ft_itoa(heredoc_i);
	file_name = ft_strjoin("/tmp/heredoc_file-",n);
	get_ms()->hd_filename = file_name;
	gc_free(n);

	heredoc_i++;

	return open(file_name,  O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
		close(get_ms()->hd_fd);
		exit(222);
	}

}
void heredoc_write(char*eof, int fd, bool expansion)
{
	signal(SIGINT,sigint_handle);
	while(1)
	{
		get_ms()->hdline = readline("> ");
		if(!get_ms()->hdline || (ft_strcmp(get_ms()->hdline,eof) == 0 &&
			(ft_strlen(get_ms()->hdline) == ft_strlen(eof))))
			break ;
		if(expansion == true)
			heredoc_expand(get_ms()->hdline);
		write(fd,get_ms()->hdline,(int)ft_strlen(get_ms()->hdline));
		write(fd,"\n",1);
		if(get_ms()->hdline)
		{
			free(get_ms()->hdline);
			get_ms()->hdline = NULL;
		}
	}
	if(get_ms()->hdline)
	{
		free(get_ms()->hdline);
		get_ms()->hdline = NULL;
	}
	close(fd);
	gc_free_all();
	exit(0);
}

int ft_create_heredoc(char*eof) //segfault when one quote but parsing handles that?
{
	bool expansion;
	int fd;
	int id;
	int wstat;

	fd = 0;
	id = 0;
	expansion = false;
	if(get_char_index(eof,'\'') == -1 && get_char_index(eof,'\"') == -1 )
		expansion = true;
	eof = remove_quotes(eof);
	if(!eof)
		eof = "\0";
	fd = open_heredoc_file(); // TODO: Handle fd=-1 ?
	get_ms()->hdline = NULL;//maybe delete
	get_ms()->heredeoc_mode = true;
	get_ms()->hd_fd = fd;
	id = fork();
	if(id == 0)
		heredoc_write(eof, fd, expansion);
	waitpid(id,&wstat,0);
	close(fd);
	if(WIFEXITED(wstat))
	{
		if(WEXITSTATUS(wstat) == 222)
		{
			return (-1);
		}
	}


	fd = open(get_ms()->hd_filename, O_RDONLY, 0777);
	get_ms()->heredeoc_mode = false;
	return (fd);
}


