/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:53:52 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/12 00:09:30 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	execute_and(t_tree *node, t_all *all)
{
	int	old_stdin;
	int	old_stdout;

	old_stdin = ft_dup(node->input, all);
	old_stdout = ft_dup(STDOUT_FILENO, all);
	if (node->here_doc)
		ft_dup2(node->here_doc, STDIN_FILENO, all);
	else
		ft_dup2(node->input, STDIN_FILENO, all);
	ft_dup2(node->output, STDOUT_FILENO, all);
	execute(node->left, all->envp, all);
	ft_dup2(all->original_in, STDIN_FILENO, all);
	ft_dup2(all->original_out, STDOUT_FILENO, all);
	if (exit_stat(0, 0) == 0)
		execute(node->right, all->envp, all);
	ft_dup2(old_stdin, STDIN_FILENO, all);
	ft_close(old_stdin, all);
	ft_dup2(old_stdout, STDOUT_FILENO, all);
	ft_close(old_stdout, all);
	return (1);
}

int	execute_or(t_tree *node, t_all *all)
{
	int	old_stdin;
	int	old_stdout;

	old_stdin = ft_dup(node->input, all);
	old_stdout = ft_dup(STDOUT_FILENO, all);
	if (node->here_doc)
		ft_dup2(node->here_doc, STDIN_FILENO, all);
	else
		ft_dup2(node->input, STDIN_FILENO, all);
	ft_dup2(node->output, STDOUT_FILENO, all);
	execute(node->left, all->envp, all);
	ft_dup2(all->original_in, STDIN_FILENO, all);
	ft_dup2(all->original_out, STDOUT_FILENO, all);
	if (exit_stat(0, 0) != 0)
		execute(node->right, all->envp, all);
	if (all->op)
	{
		execute(node->right->right, all->envp, all);
		all->op = 0;
	}
	ft_dup2(old_stdin, STDIN_FILENO, all);
	ft_close(old_stdin, all);
	ft_dup2(old_stdout, STDOUT_FILENO, all);
	ft_close(old_stdout, all);
	return (1);
}

static void	execute_parantheses(t_tree	*node, char **envp, t_all *all)
{
	int	old_stdin;
	int	old_stdout;

	old_stdin = ft_dup(node->input, all);
	old_stdout = ft_dup(STDOUT_FILENO, all);
	if (node->here_doc)
		ft_dup2(node->here_doc, STDIN_FILENO, all);
	else
		ft_dup2(node->input, STDIN_FILENO, all);
	ft_dup2(node->output, STDOUT_FILENO, all);
	execute(node->left, envp, all);
	ft_dup2(old_stdin, STDIN_FILENO, all);
	ft_close(old_stdin, all);
	ft_dup2(old_stdout, STDOUT_FILENO, all);
	ft_close(old_stdout, all);
}

int	execute(t_tree	*root, char **envp, t_all *all)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	if (!root)
		return (0);
	if (root->oper == PIPE)
		execute_pipe(root, envp, all);
	if (root->oper == PARENTHESES)
		execute_parantheses(root, envp, all);
	if (root->oper == OR)
	{
		if (root->right->oper == AND)
			all->op = 1;
		execute_or(root, all);
	}
	if (root->oper == AND)
		execute_and(root, all);
	else if (root->oper == NONE)
	{
		get_cmd_info(root, all);
		status = execute_command(root, all);
	}
	signal(SIGINT, &handle_signal);
	return (status);
}
