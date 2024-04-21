/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:20:39 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/21 10:42:35 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minibash.h"

static void	minibash_readline(char **str, t_all *all)
{
	char	*input;

	input = NULL;
	if (!all->error && !exit_stat(0, 0))
		input = readline("minibash 🙌 > ");
	else
	{
		if (all->error)
			ft_write(all->error, 2, 1);
		input = readline("minibash 💀 > ");
		all->error = NULL;
	}
	if (!input)
		*str = NULL;
	if (input)
	{
		add_history(input);
		*str = input;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_all	all;

	str = NULL;
	all.original_in = dup(STDIN_FILENO);
	all.original_out = dup(STDOUT_FILENO);
	all.error = NULL;
	all.env = parse_env(envp, &all);
	all.envp = linked_list_to_arr(&all);
	while (1)
	{
		set_delim(0, 1);
		signal(SIGINT, &handle_signal);
		signal(SIGQUIT, SIG_IGN);
		all.tree = NULL;
		minibash_readline(&str, &all);
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		get_environment(&all, &str);
		if (str[0] == 0)
		{
			free(str);
			continue ;
		}
		parse_tree(str, &all);
		if (all.error)
		{
			free(str);
			continue ;
		}
		if (set_delim(0, 0))
		{
			free(str);
			continue;
		}
		if (!all.tree->left && !all.tree->right && all.tree->oper == NONE)
		{
			// ft_write("here", 2, 1);
			int	original_in = dup(STDIN_FILENO);
			int	original_out = dup(STDOUT_FILENO);
			// fprintf(stderr, "cmd_str : %s\n", all.tree->cmd_str);
			get_cmd_info(all.tree, &all);
			// fprintf(stderr, "node->input : %d, node->output : %d node->heredoc : %d\n", all.tree->input, all.tree->output, all.tree->here_doc);
			if (all.tree->here_doc != 0)
				dup2(all.tree->here_doc, STDIN_FILENO);
			dup2(all.tree->input, STDIN_FILENO);
			dup2(all.tree->output, STDOUT_FILENO);
			if (all.tree->cmd[0] && !check_builtins(all.tree, &all))
				execute_single_command(all.tree, all.envp, &all);
			dup2(original_in, STDIN_FILENO);
			dup2(original_out, STDOUT_FILENO);
		}
		else
			execute(all.tree, all.envp, &all);
			// fprintf(stderr, "pid is : %d\n", getpid());
		free (str);
		remove_docs(&all);
		ft_open(NULL, 0, NULL, 1);
	}
	ft_malloc(0, 1, NULL);
}
