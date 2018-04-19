/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 12:56:54 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/19 12:57:11 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	welcome_message(void)
{
	char	buf[MAXPATHLEN + 1];
	char	*login;

	login = get_env_value_by_name("USER");
	ft_putstr(GREEN_FONT);
	ft_putstr(login);
	ft_strdel(&login);
	ft_putstr(BLUE_FONT);
	ft_putstr("@");
	gethostname(buf, MAXPATHLEN);
	write(1, &buf, ft_strlen(buf) - 8);
	ft_putstr(YELLOW_FONT);
	ft_putstr(" ");
	ft_bzero(buf, MAXPATHLEN);
	getcwd(buf, MAXPATHLEN);
	ft_putendl(buf);
	ft_putstr(COLOR_OFF);
	ft_putstr(" $> ");
}
