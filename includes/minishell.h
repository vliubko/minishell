/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 13:15:54 by vliubko           #+#    #+#             */
/*   Updated: 2018/03/26 14:13:34 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "sys/param.h"
# include "stdio.h"
# include "unistd.h"
# include "signal.h"

typedef	struct		s_env
{
	char 			*name;
	char 			*value;
	struct s_env	*next;
}					t_env;

t_env				*g_env;

void 				env_init(int ac, char **av, char **envp);
void				env_print();

#endif