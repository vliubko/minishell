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

void	welcome_message(void)
{
	char	buf[MAXPATHLEN + 1];
	char	*login;

	getcwd(buf, MAXPATHLEN);
	login = get_env_value_by_name("USER");
	ft_putstr(GREEN_FONT);
	ft_putstr(login);
	ft_strdel(&login);
	ft_putstr(BLUE_FONT);
	ft_putstr("@ ");
	ft_putstr(YELLOW_FONT);
	ft_putendl(buf);
	ft_putstr(COLOR_OFF);
	ft_putstr(" $> ");
}

void	get_input(char **line)
{
	char	*trim;

	get_next_line(0, &trim);
	*line = ft_strtrim(trim);
	ft_strdel(&trim);
}

void	free_env(void)
{
	t_env	*tmp;

	while (g_env)
	{
		ft_strdel(&g_env->key);
		ft_strdel(&g_env->value);
		tmp = g_env;
		free(tmp);
		g_env = g_env->next;
	}
	free(g_env);
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
