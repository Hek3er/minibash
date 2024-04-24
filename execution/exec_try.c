/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_try.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:53:52 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/24 09:05:36 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	execute_left(t_tree *node, int *fd, char **envp, t_all *all)
{
	// get_cmd_info(node, all);
	// fprintf(stderr, "node->in : %d, not->out : %d, node->here_doc : %d\n", node->input, node->output, node->here_doc);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	all->pipe_stat = execute(node, envp, all);
	exit(all->pipe_stat);
}

static void	execute_right(t_tree *node, int *fd, char **envp, t_all *all)
{
	// get_cmd_info(node, all);
	// fprintf(stderr, "node->in : %d, not->out : %d, node->here_doc : %d\n", node->input, node->output, node->here_doc);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	all->pipe_stat = execute(node, envp, all);
	exit(all->pipe_stat);
}

static void execute_pipe(t_tree *node, char **envp, t_all *all)
{
    int		fd[2];
	pid_t 	pid1;
	pid_t 	pid2;
	int		status;

	all->pipe_stat = 0;
	if (pipe(fd) == -1)
	{
		perror("");
		exit(1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("");
		exit(1); // handle error
	}
	if (pid1 == 0)
		execute_left(node->left, fd, envp, all);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("");
		exit(1); // handle error
	}
	if (pid2 == 0)
		execute_right(node->right, fd, envp, all);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	exit_stat(WEXITSTATUS(status), 1);
}

int	execute_and(t_tree *node, t_all *all)
{
	int	stat;
	int	old_stdin;
	int	old_stdout;

	old_stdin = dup(node->input);
	old_stdout = dup(STDOUT_FILENO);
	// printf("in %d out %d hd %d\n", node->input, node->output, node->here_doc);
	if (node->here_doc)
		dup2(node->here_doc, STDIN_FILENO);
	else
		dup2(node->input, STDIN_FILENO);
	dup2(node->output, STDOUT_FILENO);
	stat = execute(node->left, all->envp, all);
	if (exit_stat(0, 0) == 0)
		execute(node->right, all->envp, all);
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);
	return (1);
}

int	execute_or(t_tree *node, t_all *all)
{
	int	stat;
	int	old_stdin;
	int	old_stdout;

	old_stdin = dup(node->input);
	old_stdout = dup(STDOUT_FILENO);
	// printf("in %d out %d hd %d\n", node->input, node->output, node->here_doc);
	if (node->here_doc)
		dup2(node->here_doc, STDIN_FILENO);
	else
		dup2(node->input, STDIN_FILENO);
	dup2(node->output, STDOUT_FILENO);
	stat = execute(node->left, all->envp, all);
	if (exit_stat(0, 0) != 0)
		execute(node->right, all->envp, all);
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);
	return (1);
}

static void execute_parantheses(t_tree	*node, char **envp, t_all *all)
{
	int	old_stdin;
	int	old_stdout;

	old_stdin = dup(node->input);
	old_stdout = dup(STDOUT_FILENO);
	// printf("in %d out %d hd %d\n", node->input, node->output, node->here_doc);
	if (node->here_doc)
		dup2(node->here_doc, STDIN_FILENO);
	else
		dup2(node->input, STDIN_FILENO);
	dup2(node->output, STDOUT_FILENO);
	execute(node->left, envp, all);
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);

}

int	execute(t_tree	*root, char **envp, t_all *all)
{
	int	status;

	status = 0;
	if (!root)
		return 0;
	if (root->oper == PIPE)
	{
		execute_pipe(root, envp, all);
	}
	if (root->oper == PARENTHESES)
	{
		// execute(root->left, all->envp, all);
		execute_parantheses(root, envp, all);
		// execute(root->right, all->envp, all);
	}
	if (root->oper == OR)
	{
		execute_or(root, all);
	}
	if (root->oper == AND)
	{
		execute_and(root, all);
	}
	else if (root->oper == NONE)
	{
		// fprintf(stderr, "cmd_str : %s\n", root->cmd_str);
		get_cmd_info(root, all);
		// fprintf(stderr, "*****************cmd is : %s arg is : %s heredoc : %d in : %d out : %d\n", root->cmd[0], root->cmd root->here_doc, root->input, root->output);
		// if (!check_builtins(root, all))
		status = execute_command(root, all);
	}
	return (status);
}
