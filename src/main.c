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

//void	fork_me(char **av, char **envp)
//{
//	pid_t	process;
//
//	process = fork();
//	if (process == 0)
//	{
//		execve("/bin/ls", 0, envp); // use execve(av[0], av, envp)!
//		exit(0);
//	}
//	wait(&process);
//}

int		exe_command(char **str)
{
	//if (ft_strequ(str, "ls"))
	//	fork_me(0, 0);
	if (ft_strequ(str[0], "exit"))
		return (-1);
	if (ft_strequ(str[0], "env"))
		env_print();
	return (0);
}

int 	multi_commands(char **commands)
{
	int 	i;
	char 	**run;
	int 	ret;

	i = -1;
	while (commands[++i])
	{
		run = ft_strsplit_whitespaces(commands[i]);
		ret = exe_command(run);
		ft_free_2d_array(run);
		if (ret == -1)
			return (-1);
	}
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	char	*line;
	char 	**commands;
	int 	ret;

	(void)ac;
//	(void)av;
//	(void)envp;
	env_init(ac, av, envp);
	while (1)
	{
		welcome_message();
		get_input(&line);
		commands = ft_strsplit(line, ';');
		ret = multi_commands(commands);
		//ft_strdel(&line);
		if (ret == -1)
			break ;
	}
	return (0);
}
