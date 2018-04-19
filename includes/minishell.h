/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 13:15:54 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/18 17:02:02 by vliubko          ###   ########.fr       */
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
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

t_env				*g_env;

void				env_init(int ac, char **av, char **envp);
void				free_env(void);
int					multi_commands(char **commands);
int					check_builtins(char **command);
int					bi_echo(char **av);
int					bi_cd(char **av);
int					cd_standart(char *path);
char				*tild_replace_home(char *line);
char				*get_env_value_by_name(char *key);
void				change_env_value_by_name(char *key, char *value);
char				**list_to_array(void);
int					bi_setenv(char **command);
int					bi_unsetenv(char **command);
void				remove_env_value_by_name(char *key);
void				add_env_value(char *key, char *value);
void				welcome_message(void);
int					exe_command(char **command);

#endif
