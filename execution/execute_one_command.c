/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 04:12:03 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/11 23:27:29 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	execute_one_command(t_all *all)
{
	int	original_in;
	int	original_out;

	original_in = ft_dup(STDIN_FILENO, all);
	original_out = ft_dup(STDOUT_FILENO, all);
	get_cmd_info(all->tree, all);
	if (all->tree->here_doc != 0)
		ft_dup2(all->tree->here_doc, STDIN_FILENO, all);
	else
		ft_dup2(all->tree->input, STDIN_FILENO, all);
	ft_dup2(all->tree->output, STDOUT_FILENO, all);
	if (all->tree->cmd[0] && !check_builtins(all->tree, all))
		execute_single_command(all->tree, all->envp, all);
	ft_dup2(original_in, STDIN_FILENO, all);
	ft_close(original_in, all);
	ft_dup2(original_out, STDOUT_FILENO, all);
	ft_close(original_out, all);
}
