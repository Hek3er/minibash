/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:01:28 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/08 18:11:44 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static char	**append_str_to_arr(char *cmd, t_tree *b, int index, t_all *all)
{
	int		i;
	char	**new_cmds;
	int		size;

	i = 0;
	size = arr_size(b->cmd) + 2;
	new_cmds = ft_malloc(size * sizeof(char *), 0, all);
	while (i < index)
	{
		new_cmds[i] = b->cmd[i];
		i++;
	}
	new_cmds[i] = cmd;
	i++;
	while (i < size - 1)
	{
		new_cmds[i] = b->cmd[i - 1];
		i++;
	}
	new_cmds[i] = NULL;
	return (new_cmds);
}

int	cmp_q(char *str, char *cmd, t_all *all)
{
	char	*cmd_without_quote[2];

	cmd_without_quote[0] = cmd;
	cmd_without_quote[1] = NULL;
	remove_quotes(cmd_without_quote, all);
	return (ft_strcmp(cmd_without_quote[0], str));
}

void	compare_arrays(t_tree *b, char **arr, t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (b->cmd && b->cmd[i])
	{
		if ((cond_oper(b->cmd[i], INPUT) || cond_oper(b->cmd[i], H_DOC) || \
		cond_oper(b->cmd[i], OUTPUT) || cond_oper(b->cmd[i], APPEND) \
		|| !arr[j]))
		{
			move_element(b, i);
			move_element(b, i);
		}
		else if (ft_strcmp(arr[j], b->cmd[i]) && cmp_q(arr[j], b->cmd[i], all))
			b->cmd = append_str_to_arr(arr[j], b, i, all);
		else
		{
			i++;
			if (arr[j])
				j++;
		}
	}
}
