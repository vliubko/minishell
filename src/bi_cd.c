//
// Created by Vadym LIUBKO on 4/16/18.
//

#include "minishell.h"


char    *tild_replace_home(char *line)
{
    char *new_line;
    char *home;
    char *find_after;

    if (!(find_after = ft_strchr(line, '~')))
		return (ft_strdup(line));
	find_after++;
    if (*find_after == '\0' || *find_after == '/')
    {
        home = get_env_value_by_name("HOME");
        new_line = ft_strjoin_free(home, find_after, 0);
        ft_strdel(&line);
        return (new_line);
    }
	return (ft_strdup(line));
}


static int    cd_access_check(char *path, int count_args)
{
    struct stat		f;
	char			buf[MAXPATHLEN];

	ft_strcpy(buf, "cd: ");
    if (count_args > 1)
    {
        ft_putendl("Too many arguments.");
    }
    else if (lstat(path, &f) == -1)
    {
		ft_putstr(ft_strcat(buf, path));
        ft_putendl(": No such directory.");
    }
    else if (S_ISREG(f.st_mode))
    {
		ft_putstr(ft_strcat(buf, path));
        ft_putendl(": Not a directory.");
    }
    else if (!(f.st_mode & S_IXUSR))
    {
		ft_putstr(ft_strcat(buf, path));
        ft_putendl(": Permission denied.");
    }
	else
    	return (0);
	return (1);
}

int     cd_standart (char *path)
{
	char dir[MAXPATHLEN];

	getcwd(dir, MAXPATHLEN);
	change_env_value_by_name("OLDPWD", dir);
    chdir(path);
	getcwd(dir, MAXPATHLEN);
	change_env_value_by_name("PWD", dir);
    ft_strdel(&path);
    return (1);
}

int     bi_cd(char **arg)
{
    char    *new_path;
    int     count_args;

    count_args = ft_count_elems(NULL, arg, 2);

    if (count_args == 0)
        new_path = get_env_value_by_name("HOME");
    else if (ft_strequ("-", arg[0]) && count_args == 1)
        new_path = get_env_value_by_name("OLDPWD");
    else
        new_path = ft_strdup(arg[0]);
    if (cd_access_check(new_path, count_args) == 1)
	{
		ft_strdel(&new_path);
		return (1);
	}
    return (cd_standart(new_path));
}