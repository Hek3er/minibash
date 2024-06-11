/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_right_left.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:46:27 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/11 23:04:07 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	execute_left(t_tree *node, int *fd, char **envp, t_all *all)
{
	int	status;

	ft_dup2(fd[1], STDOUT_FILENO, all);
	ft_close(fd[0], all);
	ft_close(fd[1], all);
	status = execute(node, envp, all);
	exit(status);
}

void	execute_right(t_tree *node, int *fd, char **envp, t_all *all)
{
	int	status;

	ft_dup2(fd[0], STDIN_FILENO, all);
	ft_close(fd[1], all);
	ft_close(fd[0], all);
	status = execute(node, envp, all);
	exit(status);
}
