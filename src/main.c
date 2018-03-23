
#include "minishell.h"

void 	welcome_message(void)
{
	//char	*cwd;
	char 	buf[MAXPATHLEN + 1];


	getcwd(buf, MAXPATHLEN);
	ft_putstr(buf);
	ft_putstr(" $> ");
}

void	get_input(char **line)
{
	char *trim;

	get_next_line(0, &trim);
	*line = ft_strtrim(trim);
}

int 	main(int ac, char **av, char **envp)
{
	char *line;
	(void)ac;
	(void)av;
	(void)envp;

	while (1)
	{
		welcome_message();
		get_input(&line);
		if (ft_strcmp(line, "exit") == 0)
			exit (0);
		ft_strdel(&line);
	}
	return (0);
}
