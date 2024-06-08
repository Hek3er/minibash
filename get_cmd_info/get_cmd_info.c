/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 08:15:38 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/08 17:47:56 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	remove_empty_element(t_tree *branch)
{
	int	i;

	i = 0;
	while (branch->cmd && branch->cmd[i])
	{
		if (!branch->cmd[i][0])
			move_element(branch, i);
		else
			i++;
	}
}

static void	get_cmd_array_quotes(t_tree *branch, t_all *all, \
char **str, int quote)
{
	int	i;

	i = 0;
	*str = ft_strdup(branch->cmd_str, all);
	all->add_quotes_to_env = quote;
	branch->cmd = split_by_space(*str, all, 1);
	while (branch->cmd && branch->cmd[i])
	{
		get_environment(all, branch->cmd + i);
		if (branch->cmd[i] && branch->cmd[i][0])
			seperate_env(branch, all, i, &i);
		else
			i++;
	}
}

int	get_cmd_info(t_tree *branch, t_all *all)
{
	char	**pre_env_arr;
	char	*str;
	char	**arr_check;

	all->error = NULL;
	pre_env_arr = split_by_space(branch->cmd_str, all, 1);
	get_cmd_array_quotes(branch, all, &str, 1);
	get_input_output(branch->cmd, branch, pre_env_arr, all);
	remove_quotes(branch->cmd, all);
	arr_check = branch->cmd;
	get_cmd_array_quotes(branch, all, &str, 0);
	remove_redirectionals(branch, arr_check, all);
	arr_check = branch->cmd;
	get_cmd_array_quotes(branch, all, &str, 1);
	compare_arrays(branch, arr_check, all);
	remove_quotes(branch->cmd, all);
	branch->cmd = get_wildcard(branch->cmd, all);
	if (branch->here_doc == 0)
		branch->here_doc = \
		get_here_doc(str, &branch->input, branch->doc_i, all);
	all->envp = linked_list_to_arr(all);
	remove_empty_element(branch);
	if (all->error)
		return (1);
	return (0);
}
