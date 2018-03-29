/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 14:37:52 by vliubko           #+#    #+#             */
/*   Updated: 2018/03/28 14:45:09 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		echo_print(char *str)
{
	char	*ret;
	int		i;

	i = -1;
	ret = str;
	if (ft_strchr(ret, 34) != NULL || ft_strchr(ret, 39) != NULL)
	{
		while (ret[++i])
		{
			if (ret[i] == 34 || ret[i] == 39)
				continue ;
			write(1, &ret[i], 1);
		}
	}
	else
		ft_putstr(ret);
	ft_putstr(COLOR_OFF);
}

static int		echo_dollar_sign(char *str)
{
	char	*ret;
	char	*value;
	int		i;

	i = -1;
	while (str[++i] != '$')
	{
		if (str[i] == 34 || str[i] == 39)
			continue ;
		write(1, &str[i], 1);
	}
	ret = ft_strchr(str, '$') + 1;
	value = env_value_by_name(ret);
	if (value)
	{
		ft_putstr(value);
		ft_strdel(&value);
		return (1);
	}
	return (0);
}

static void		newline_check(int flag)
{
	if (!flag)
		write(1, "\n", 1);
	else
	{
		ft_putstr(INVERTED);
		ft_putstr("%");
		ft_putstr(COLOR_OFF);
		ft_putstr("\n");
	}
}

void			echo_run(char **av, int i)
{
	while (av[++i])
	{
		if (ft_strchr(av[i], '$'))
		{
			echo_dollar_sign(av[i]);
			if (av[i + 1])
				ft_putstr(" ");
			continue;
		}
		echo_print(av[i]);
		if (av[i + 1])
			ft_putstr(" ");
	}
}

int				bi_echo(char **av)
{
	int		i;
	int		echo_n;

	echo_n = 0;
	if (!av[0])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (av[0][0] == '-' && av[0][1] == 'n' && av[0][2] == '\0')
		echo_n = 1;
	i = -1;
	if (echo_n)
		i++;
	echo_run(av, i);
	newline_check(echo_n);
	return (1);
}
