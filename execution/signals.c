/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 05:52:47 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/07 14:57:17 by azainabi         ###   ########.fr       */
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
		exit_stat(1, 1);
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

void	reset_terminal(void)
{
	struct	termios term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	term.c_oflag = OPOST | ONLCR;
	term.c_lflag = ICANON | ECHO | ECHOE | ECHOK | ISIG;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	handle_signal_dfl(int sig)
{
	if (sig == SIGINT)
		exit(130);
	if (sig == SIGQUIT)
	{
		reset_terminal();
		exit(131);
	}
}
