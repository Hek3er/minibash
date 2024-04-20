/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:37:18 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/18 23:22:24 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	execute_single_command(t_tree *node, char **envp, t_all *all)
{
	char	*path = get_cmd_path(all, node->cmd[0]);
	pid_t	pid;
	int		perm;
	int		stat;

	perm = 0;
	if (!path)
	{
		all->tmp = ft_strjoin("minibash: ", node->cmd[0], all);
		all->error = ft_strjoin(all->tmp, ": command not found", all);
		exit_stat(127, 1);
		return ;
	}
	is_a_dir(path, &perm);
	if (perm)
	{
		if (perm == 2)
		{
			all->tmp = ft_strjoin("minibash: ", path, all);
			all->error = ft_strjoin(all->tmp, ": is a directory", all);
		}
		else
		{
			all->tmp = ft_strjoin("minibash: ", path, all);
			all->error = ft_strjoin(all->tmp, ": Permission denied", all);
		}
		exit_stat(126, 1);
		return ;
	}
	// fprintf(stderr, "here\n");
	
	pid = fork();
	if (pid == -1)
	{
		perror("");
		exit(1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(path, node->cmd, envp) == -1)
		{
			perror("minibash: ");
			exit(1);
		}
	}
	waitpid(pid, &stat, 0);
	exit_stat(WEXITSTATUS(stat), 1);
}
