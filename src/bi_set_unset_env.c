/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_set_unset_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:14:59 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/18 17:15:05 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_forbidden_env(char *key)
{
	if (!ft_strequ(key, "HOME") && !ft_strequ(key, "PWD") &&
		!ft_strequ(key, "OLDPWD") && !ft_strequ(key, "USER") &&
		!ft_strequ(key, "LOGNAME"))
		return (0);
	ft_putstr_fd("Forbidden to unset: HOME, PWD, OLDPWD, USER, LOGNAME\n", 2);
	return (1);
}

int		bi_unsetenv(char **command)
{
	char	*key;
	char	*find;

	if (!command[0] || command[1])
		ft_putstr_fd("Usage: unsetenv NAME\n", 2);
	key = command[0];
	check_forbidden_env(key);
	if ((find = get_env_value_by_name(key)))
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

int		bi_setenv(char **command)
{
	char	*key;
	char	*value;
	char	*find;

	if (!command[0] || command[1] || !(ft_strchr(command[0], '=')) ||
		command[0][0] == '=')
		ft_putstr_fd("Usage: setenv [NAME]=[VALUE]\n", 2);
	else
	{
		key = ft_strsub(command[0], 0, ft_strchr(command[0], '=') - command[0]);
		if (check_forbidden_env(key) != 1)
		{
			value = ft_strchr(command[0], '=') + 1;
			if ((find = get_env_value_by_name(key)))
			{
				change_env_value_by_name(key, value);
				ft_strdel(&find);
			}
			else
				add_env_value(key, value);
		}
		(key) ? ft_strdel(&key) : 0;
	}
	return (1);
}
