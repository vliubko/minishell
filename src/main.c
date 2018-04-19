/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 11:21:36 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/18 16:58:56 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(char **line)
{
	char	*trim;

	get_next_line(0, &trim);
	*line = ft_strtrim(trim);
	ft_strdel(&trim);
}

int		multi_commands(char **commands)
{
	int		i;
	char	**run;
	int		ret;

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

void	signal_check(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		welcome_message();
		signal(SIGINT, signal_check);
	}
}

int		main(int ac, char **av, char **envp)
{
	char	*line;
	char	**commands;
	int		ret;

	(void)ac;
	env_init(ac, av, envp);
	while (1)
	{
		welcome_message();
		signal(SIGINT, signal_check);
		get_input(&line);
		commands = ft_strsplit(line, ';');
		if (line)
			ft_strdel(&line);
		ret = multi_commands(commands);
		ft_free_2d_array(commands);
		if (ret == -1)
		{
			free_env();
			break ;
		}
	}
	return (0);
}
