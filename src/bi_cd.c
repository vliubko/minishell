//
// Created by Vadym LIUBKO on 4/16/18.
//

#include "minishell.h"


char    *tild_replace_home(char *line)
{
    char *new_line;
    char *home;
    char *find_space_before;
    char *find_after;

    find_space_before = ft_strchr(line, '~');
    find_space_before--;
    find_after = ft_strchr(line, '~');
    find_after++;

    if ((*find_space_before) == ' ' && ((*find_after) == '/0' || (*find_after) == '/'))
    {
        home = get_env_value_by_name("HOME");
        new_line = ft_strjoin_free(home, line);
        return (new_line);
    }
    return (line);
}

int     bi_cd(char **arg)
{
    char *home;
    char *new_line;

    if (ft_count_elems(NULL, arg, 2) > 1)
    {
        ft_putstr("cd: Too many arguments.");
        return (1);
    }
    else if (ft_count_elems(NULL, arg, 2) == 0)
    {
        home = get_env_value_by_name("HOME");
        chdir(home);
    }
    else if (ft_strchr(arg[0], '~'))
    {
        new_line = tild_replace_home(arg[0]);
        chdir(arg[0]);
        // дописать тут !!!
    }
    return (1);
}