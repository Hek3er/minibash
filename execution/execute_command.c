/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:34:59 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/24 09:04:23 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	handle_redirections_exec(t_tree *node)
{
	if (node->here_doc != 0)
	{
		// write(2, "here\n", 5);
		// fprintf(stderr, "*****************************************************************node->heredoc : %d\n", node->here_doc);
		dup2(node->here_doc, STDIN_FILENO);
		// close(node->here_doc);
	}
	if (node->input != 0)
	{
		fprintf(stderr, "node->input : %d\n", node->input);
		dup2(node->input, STDIN_FILENO);
		// close(node->input);
		fprintf(stderr, "STDIN_FILENO : %d\n", STDIN_FILENO);
	}
	if (node->output != 1)
		dup2(node->output, STDOUT_FILENO);
}

int	execute_command(t_tree *node, t_all *all)
{
	char		*path;
	pid_t		id;
	int			status;
	int			perm;

	// fprintf(stderr, "node->in : %d, not->out : %d, node->here_doc : %d\n", node->input, node->output, node->here_doc);
	perm = 0;
	handle_redirections_exec(node);
	if (node->cmd[0] == NULL)
		return 0;
	// fprintf(stderr, "node->stdin : %d, not->srdout : %d, node->here_doc : %d\n", STDIN_FILENO, STDOUT_FILENO, node->here_doc);
	if (check_builtins(node, all))
	{
		dup2(all->original_in, STDIN_FILENO);
		dup2(all->original_out, STDOUT_FILENO);
		return (0);
	}
	signal(SIGINT, SIG_DFL);
	id = fork();
	if (id == -1)
	{
		perror("");
		exit(14);
	}
	if (id == 0)
	{
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
		// handle_redirections_exec(node, path, all);
		if (execve(path, node->cmd, all->envp) == -1)
		{
			perror("");
			exit(111);
		}
	}
	waitpid(id, &status, 0);
	exit_stat(WEXITSTATUS(status), 1); // check if this is true
	// fprintf(stderr, "exit stat is   : %d pid : %d\n", WEXITSTATUS(status), getpid());
	return (WEXITSTATUS(status));
}
