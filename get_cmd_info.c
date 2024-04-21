/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 08:15:38 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/21 01:31:55 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minibash.h"


int	get_cmd_info(t_tree *branch, t_all *all)
{
	char	**pre_env_arr;
	char	*str;

	all->error = NULL;
	str = branch->cmd_str;
	pre_env_arr = split_by_space(str, all);
	branch->cmd = split_by_space(str, all);
//	branch->cmd = get_wildcard(branch->cmd, all);
	get_environment(all, &str);
	branch->input = get_input_output(branch->cmd, 0, pre_env_arr, all);
	branch->output = get_input_output(branch->cmd, 1, pre_env_arr, all);
	if (branch->here_doc == 0)
		branch->here_doc = get_here_doc(str, &branch->input, branch->doc_i, all);
	all->envp = linked_list_to_arr(all);
	if (all->error)
		return (1);
	return (0);
}

