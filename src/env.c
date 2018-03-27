/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:09:06 by vliubko           #+#    #+#             */
/*   Updated: 2018/03/26 14:21:54 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_print(void)
{
	t_env	*print;

	print = g_env;
	while (print)
	{
		ft_putstr(print->name);
		ft_putstr("=");
		ft_putendl(print->value);
		print = print->next;
	}
}


void	env_init(int ac, char **av, char **envp)
{
	int		i;
	t_env	*head;

	(void)ac;
	(void)av;
	i = 0;
	g_env = (t_env*)ft_memalloc(sizeof(t_env));
	head = g_env;
	while (envp[i])
	{
		g_env->name = ft_strsub(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		g_env->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (!envp[++i])
			break ;
		g_env->next = (t_env*)ft_memalloc(sizeof(t_env));
		g_env = g_env->next;
	}
	g_env = head;
}
