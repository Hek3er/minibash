/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 05:52:47 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/21 06:38:40 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	set_delim(int flag, int set)
{
	static int	x = 0;
	
	if (set == 1)
		x = flag;
	return (x);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		exit_stat(2, 1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signal_doc(int sig)
{
	if (sig == SIGINT)
	{
		exit_stat(1, 1);
		set_delim(1, 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}
