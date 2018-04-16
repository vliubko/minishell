//
// Created by Vadym LIUBKO on 4/16/18.
//

#include "minishell.h"

int 	check_builtins(char **command)
{
    if (ft_strequ(command[0], "exit"))
        return (-1);
    if (ft_strequ(command[0], "echo"))
        return (bi_echo(command + 1));
    if (ft_strequ(command[0], "cd"))
        return (bi_cd(command + 1));
    return (0);
}

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

int 	check_bins(char **command)
{
    char			**path;
    int				i;
    char			*full_path;
    struct stat		f;
    char 			*leak;

    leak = get_env_value_by_name("PATH");
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