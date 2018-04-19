/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:42:46 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/18 16:42:57 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		bi_clear(void)
{
	ft_putstr("\033[2J\033[1;1H");
	return (1);
}

int		bi_env(void)
{
	t_env	*print;

	print = g_env;
	while (print)
	{
		ft_putstr(print->key);
		ft_putstr("=");
		ft_putendl(print->value);
		print = print->next;
	}
	return (1);
}

int		check_builtins(char **command)
{
	if (ft_strequ(command[0], "exit"))
		return (-1);
	if (ft_strequ(command[0], "echo"))
		return (bi_echo(command + 1));
	if (ft_strequ(command[0], "cd"))
		return (bi_cd(command + 1));
	if (ft_strequ(command[0], "clear"))
		return (bi_clear());
	if (ft_strequ(command[0], "env"))
		return (bi_env());
	if (ft_strequ(command[0], "setenv"))
		return (bi_setenv(command + 1));
	if (ft_strequ(command[0], "unsetenv"))
		return (bi_unsetenv(command + 1));
	return (0);
}
