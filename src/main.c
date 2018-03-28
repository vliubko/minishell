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

char 	*env_value_by_name(char *str)
{
	t_env	*tmp;

	tmp = g_env;

	while (tmp)
	{
		if (ft_strequ(tmp->name, str))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	welcome_message(void)
{
	char	buf[MAXPATHLEN + 1];
	char 	*login;

	getcwd(buf, MAXPATHLEN);
	login = env_value_by_name("USER");
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

char 	**list_to_array(void)
{
	t_env	*list;
	char 	**ret;
	char 	*tmp;
	int 	new_size;

	list = g_env;
	new_size = 0;
	while (list)
	{
		new_size++;
		list = list->next;
	}
	ret = (char**)malloc((sizeof(char*) * (new_size + 1)));
	list = g_env;
	new_size = 0;
	while (list)
	{
		tmp = ft_strjoin(list->name, "=");
		ret[new_size] = ft_strjoin(tmp, list->value);
		ft_strdel(&tmp);
		new_size++;
		list = list->next;
	}
	ret[new_size] = NULL;
	return (ret);
}

int 	check_builtins(char **command)
{
	if (ft_strequ(command[0], "exit"))
		return (-1);
	if (ft_strequ(command[0], "echo"))
		return (bi_echo(command + 1));
	return (0);
}

int 	fork_run_cmd(char *path, char **av)
{
	pid_t	process;
	char 	**envp;

	process = fork();
	envp = list_to_array();
	if (process == 0)
	{
		execve(path, av, envp); // use execve(av[0], av, envp)!
		exit(0);
	}
	wait(&process);
	ft_free_2d_array(envp);
	if (path)
		ft_strdel(&path);
	return (1);
}

int 	access_check(char *path, struct stat f, char **command)
{
	if (f.st_mode & S_IFREG)
	{
		if (f.st_mode & S_IXUSR)
			return (fork_run_cmd(path, command));
		else
		{
			ft_putstr("minishell: permission denied: ");
			ft_putendl(path);
		}
		ft_strdel(&path);
		return (1);
	}
	ft_strdel(&path);
	return (0);
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

int 	check_bins(char **command)
{
	char			**path;
	int				i;
	char			*full_path;
	struct stat		f;
	char 			*leak;

	leak = env_value_by_name("PATH");
	path = ft_strsplit(leak, ':');
	ft_strdel(&leak);
	i = -1;
	while (path && path[++i])
	{
		if (*command[0] == '/')
			full_path = ft_strdup(command[0]);
		else
			full_path = ft_pathjoin(path[i], command[0]);
		if (lstat(full_path, &f) == -1)
			ft_strdel(&full_path);
		else
		{
			ft_free_2d_array(path);
			return (access_check(full_path, f, command));
		}
	}
	ft_free_2d_array(path);
	return (0);
}

int		exe_command(char **command)
{
	int 	bi;

	if ((bi = check_builtins(command)) == 1 || check_bins(command))
		return (1);
	if (bi == -1)
		return (-1);
	ft_putstr("minishell: command not found: ");
	ft_putendl(command[0]);
	//if (ft_strequ(str, "ls"))
	//	fork_me(0, 0);
//	if (ft_strequ(str[0], "exit"))
//		return (-1);
//	if (ft_strequ(str[0], "env"))
//		env_print();
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

void 	print_list(void)
{
	t_env *list;

	list = g_env;

	while(list)
	{
		printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}
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
		//print_list ();
		get_input(&line);
		commands = ft_strsplit(line, ';');
		if (line)
			ft_strdel(&line);
		ret = multi_commands(commands);
		ft_free_2d_array(commands);
		if (ret == -1)
			break ;
	}
	return (0);
}
