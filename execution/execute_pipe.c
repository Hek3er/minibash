/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:05:24 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/17 03:10:28 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static int	execute_left_right(t_tree *node, char **envp, int *fd, t_all *all)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
	{
		ft_write(FORK_ERROR, 2, 1);
		exit(1);
	}
	if (pid1 == 0)
		execute_left(node->left, fd, envp, all);
	pid2 = fork();
	if (pid2 == -1)
	{
		ft_write(FORK_ERROR, 2, 1);
		exit(1);
	}
	if (pid2 == 0)
		execute_right(node->right, fd, envp, all);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &all->status, 0);
	waitpid(pid2, &all->status, 0);
	return (all->status);
}

void	execute_pipe(t_tree *node, char **envp, t_all *all)
{
	int	fd[2];

	all->pipe_stat = 0;
	if (pipe(fd) == -1)
	{
		ft_write(PIPE_ERROR, 2, 1);
		exit(1);
	}
	execute_left_right(node, envp, fd, all);
	exit_stat(WEXITSTATUS(all->status), 1);
}
