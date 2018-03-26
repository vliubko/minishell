/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 11:21:36 by vliubko           #+#    #+#             */
/*   Updated: 2018/03/26 14:11:47 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	welcome_message(void)
{
	char	buf[MAXPATHLEN + 1];

	getcwd(buf, MAXPATHLEN);
	ft_putstr(buf);
	ft_putstr(" $> ");
}

void	get_input(char **line)
{
	char	*trim;

	get_next_line(0, &trim);
	*line = ft_strtrim(trim);
	ft_strdel(&trim);
}

void	fork_me(char **av, char **envp)
{
	pid_t	process;

	process = fork();
	if (process == 0)
	{
		execve("/bin/ls", av, envp); // use execve(av[0], av, envp)!
		exit(0);
	}
	wait(&process);
}

int		main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac;
//	(void)av;
//	(void)envp;
	init_env(ac, av, envp);
	while (1)
	{
		welcome_message();
		get_input(&line);
		if (ft_strequ(line, "ls"))
			fork_me(av, envp);
		if (ft_strequ(line, "exit"))
		{
			ft_strdel(&line);
			exit(0);
		}
		ft_strdel(&line);
	}
	return (0);
}
