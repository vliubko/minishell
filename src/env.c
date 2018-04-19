/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:09:06 by vliubko           #+#    #+#             */
/*   Updated: 2018/03/30 11:16:26 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(void)
{
	t_env	*tmp;

	while (g_env)
	{
		ft_strdel(&g_env->key);
		ft_strdel(&g_env->value);
		tmp = g_env;
		free(tmp);
		g_env = g_env->next;
	}
	free(g_env);
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
		g_env->key = ft_strsub(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		g_env->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (!envp[++i])
			break ;
		g_env->next = (t_env*)ft_memalloc(sizeof(t_env));
		g_env = g_env->next;
	}
	g_env = head;
}
