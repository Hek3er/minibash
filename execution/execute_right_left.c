/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_right_left.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:46:27 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/16 15:06:18 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	execute_left(t_tree *node, int *fd, char **envp, t_all *all)
{
	int	status;

	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	status = execute(node, envp, all);
	exit(status);
}

void	execute_right(t_tree *node, int *fd, char **envp, t_all *all)
{
	int	status;

	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	status = execute(node, envp, all);
	exit(status);
}
