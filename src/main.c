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
	char 	*login;

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

char 	*ft_pathjoin(char *p1, char *p2)
{
	char	*tmp;
	char 	*ret;

	if (!p2 || !p1)
		return (NULL);
	if (p1[ft_strlen(p1)] != '/')
		tmp = ft_strjoin(p1, "/");
	else
		tmp = ft_strdup(p1);
	ret = ft_strjoin(tmp, p2);
	ft_strdel(&tmp);
	return (ret);
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


void 	print_list(void)
{
	t_env *list;

	list = g_env;

	while(list)
	{
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
}

void	free_env(void)
{
	t_env *tmp;

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
	char 	**commands;
	int 	ret;

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
			break;
		}
	}
	return (0);
}
