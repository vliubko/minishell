//
// Created by Vadym LIUBKO on 4/17/18.
//

#include "minishell.h"

char 	**list_to_array(void)
{
    t_env	*list;
    char 	**ret;
    char 	*tmp;
    int 	new_size;

    list = g_env;
    new_size = ft_count_elems((t_list*)list, NULL, 1);
    ret = (char**)malloc((sizeof(char*) * (new_size + 1)));
    new_size = 0;
    while (list)
    {
        tmp = ft_strjoin(list->key, "=");
        ret[new_size] = ft_strjoin(tmp, list->value);
        ft_strdel(&tmp);
        new_size++;
        list = list->next;
    }
    ret[new_size] = NULL;
    return (ret);
}

char 	*get_env_value_by_name(char *key)
{
    t_env	*tmp;

    tmp = g_env;

    while (tmp)
    {
        if (ft_strequ(tmp->key, key))
            return (ft_strdup(tmp->value));
        tmp = tmp->next;
    }
    return (NULL);
}

void    change_env_value_by_name(char *key, char *value)
{
    t_env   *tmp;
	char 	*leak_remove;
    tmp = g_env;

    while (tmp)
    {
        if (ft_strequ(tmp->key, key))
        {
			leak_remove = tmp->value;
            tmp->value = ft_strdup(value);
			ft_strdel(&leak_remove);
            return ;
        }
        tmp = tmp->next;
    }
}

void    add_env_value(char *key, char *value)
{
    t_env   *tmp;
    t_env   *new_node;

    tmp = g_env;

    new_node = (t_env*)ft_memalloc(sizeof(t_env));
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;

    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

void	remove_env_value_by_name(char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = g_env;
	prev = NULL;
	while (!(ft_strequ(tmp->key, key)) && tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (ft_strequ(tmp->key, key))
	{
		if (prev)
			prev->next = tmp->next;
		else
			g_env = tmp->next;
		ft_strdel(&tmp->key);
		ft_strdel(&tmp->value);
		free(tmp);
	}
}

int 	bi_unsetenv(char **command)
{
	char	*key;
	char 	*find;

	if (!command[0] || command[1])
		ft_putstr_fd("Usage: unsetenv NAME\n", 2);
	key = command[0];
	if (ft_strequ(key, "HOME") || ft_strequ(key, "PWD") || ft_strequ(key, "OLDPWD"))
		ft_putstr_fd("Please, don't change this variables: HOME, PWD, OLDPWD\n", 2);
	else if ((find = get_env_value_by_name(key)))
	{
		remove_env_value_by_name(key);
		ft_strdel(&find);
	}
	else
	{
		ft_putstr_fd(key, 2);
		ft_putstr_fd(" not found in env\n", 2);
	}
	return (1);
}

int 	bi_setenv(char **command)
{
	char	*key;
	char	*value;
	char 	*find;

	if (!command[0] || command[1] || !(ft_strchr(command[0], '=')) ||
		command[0][0] == '=')
		ft_putstr_fd("Usage: setenv [NAME]=[VALUE]\n", 2);
	else
	{
		key = ft_strsub(command[0], 0, ft_strchr(command[0], '=') - command[0]);
		if (ft_strequ(key, "HOME") || ft_strequ(key, "PWD") || ft_strequ(key, "OLDPWD") ||
				ft_strequ(key, "USER") || ft_strequ(key, "LOGNAME"))
		{
			ft_putstr_fd("Forbidden to unset: HOME, PWD, OLDPWD, USER, LOGNAME\n", 2);
			ft_strdel(&key);
			return (1);
		}
		value = ft_strchr(command[0], '=') + 1;
		if ((find = get_env_value_by_name(key)))
		{
			change_env_value_by_name(key, value);
			ft_strdel(&find);
		}
		else
			add_env_value(key, value);
		(key) ? ft_strdel(&key) : 0;
	}
	return (1);
}