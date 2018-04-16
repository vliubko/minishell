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
# include "sys/stat.h"

# define BLUE_FONT "\e[38;5;69m"
# define RED_FONT "\e[38;5;196m"
# define GREEN_FONT "\e[38;5;46m"
# define YELLOW_FONT "\e[38;5;226m"
# define COLOR_OFF "\e[0m"
# define INVERTED 	"\e[7m"

typedef	struct		s_env
{
	char 			*name;
	char 			*value;
	struct s_env	*next;
}					t_env;

t_env				*g_env;

void 				env_init(int ac, char **av, char **envp);
void				env_print();
int 				multi_commands(char **commands);
int					bi_echo(char **av);
char 	            *ft_pathjoin(char *p1, char *p2);
int					bi_cd(char **av);
char 				*get_env_value_by_name(char *str);


#endif