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