/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 04:12:03 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/04 16:21:21 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	execute_one_command(t_all *all)
{
	int	original_in;
	int	original_out;

	original_in = dup(STDIN_FILENO);
	original_out = dup(STDOUT_FILENO);
	get_cmd_info(all->tree, all);
	if (all->tree->here_doc != 0)
		dup2(all->tree->here_doc, STDIN_FILENO);
	else
		dup2(all->tree->input, STDIN_FILENO);
	dup2(all->tree->output, STDOUT_FILENO);
	if (all->tree->cmd[0] && !check_builtins(all->tree, all))
		execute_single_command(all->tree, all->envp, all);
	dup2(original_in, STDIN_FILENO);
	close(original_in);
	dup2(original_out, STDOUT_FILENO);
	close(original_out);
}
