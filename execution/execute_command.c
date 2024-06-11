/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:34:59 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/11 23:20:21 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	error_execve(char *str, t_all *all)
{
	ft_write("minibash: ", 2, 0);
	ft_write(str, 2, 0);
	ft_write(": ", 2, 0);
	ft_write(strerror(errno), 2, 1);
	ft_exit(NULL, all);
}

static void	handle_redirections_exec(t_tree *node, t_all *all)
{
	if (node->here_doc != 0)
		ft_dup2(node->here_doc, STDIN_FILENO, all);
	if (node->input != 0)
		ft_dup2(node->input, STDIN_FILENO, all);
	if (node->output != 1)
		ft_dup2(node->output, STDOUT_FILENO, all);
}

static void	execution_child_command(t_tree *node, int perm, \
			char *path, t_all *all)
{
	if (perm)
	{
		if (perm == 2)
		{
			ft_write("minibash: ", 2, 0);
			ft_write(path, 2, 0);
			ft_write(": is a directory", 2, 1);
		}
		else
		{
			ft_write("minibash: ", 2, 0);
			ft_write(path, 2, 0);
			ft_write(": Permission denied", 2, 1);
		}
		exit_stat(126, 1);
		exit(126);
	}
	if (execve(path, node->cmd, all->envp) == -1)
		error_execve(node->cmd[0], all);
}

static void	execution_child(t_tree *node, int perm, char *path, t_all *all)
{
	all->id = fork();
	if (all->id == -1)
	{
		ft_write(FORK_ERROR, 2, 1);
		ft_exit(NULL, all);
	}
	if (all->id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		path = get_cmd_path(all, node->cmd[0]);
		if (!path)
		{
			ft_write("minibash: ", 2, 0);
			ft_write(node->cmd[0], 2, 0);
			ft_write(": command not found", 2, 1);
			exit_stat(127, 1);
			exit(127);
		}
		is_a_dir(path, &perm);
		execution_child_command(node, perm, path, all);
	}
}

int	execute_command(t_tree *node, t_all *all)
{
	char		*path;
	int			status;
	int			perm;

	perm = 0;
	path = NULL;
	handle_redirections_exec(node, all);
	if (!node->cmd || node->cmd[0] == NULL || node->cmd[0][0] == '\0')
		return (0);
	if (check_builtins(node, all))
	{
		ft_dup2(all->original_in, STDIN_FILENO, all);
		ft_dup2(all->original_out, STDOUT_FILENO, all);
		return (0);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	execution_child(node, perm, path, all);
	waitpid(all->id, &status, 0);
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	return (exit_stat(WEXITSTATUS(status), 1), WEXITSTATUS(status));
}
