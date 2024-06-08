/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:47:29 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/08 18:10:19 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	open_file(char *str, int oper_size, int expected, t_all *all)
{
	int	fd;

	fd = 0;
	if (expected == 0)
		fd = ft_open(str, OPEN_READ, all, 0);
	else if (expected == 1)
	{
		if (oper_size == 1)
			fd = ft_open(str, OPEN_TRUNC, all, 0);
		else if (oper_size == 2)
			fd = ft_open(str, OPEN_APPEND, all, 0);
	}
	return (fd);
}

static void	check_if_output(char **arr_pre[2], t_all *all, t_tree *b, int *i)
{
	int	cnd_oper_type;

	cnd_oper_type = (cond_oper(*arr_pre[0], OUTPUT) || \
	cond_oper(*arr_pre[0], APPEND));
	if (cnd_oper_type)
		b->output = \
		open_file(arr_pre[0][1], cond_redirect(*arr_pre[0]), 1, all);
	else
	{
		cnd_oper_type = cond_oper(*arr_pre[0], INPUT);
		if (cnd_oper_type)
			b->input = \
			open_file(arr_pre[0][1], cond_redirect(*arr_pre[0]), 0, all);
	}
	if (cnd_oper_type || cond_oper(*arr_pre[0], H_DOC))
	{
		(*i) += 2;
	}
	else
		(*i)++;
}

void	get_input_output(char **arr, t_tree *branch, char **pre, t_all *all)
{
	int	i;

	i = 0;
	if ((!arr) || (arr[i] && (cond_oper(arr[i], INPUT) || \
	cond_oper(arr[i], OUTPUT) || cond_oper(arr[i], APPEND)) && !arr[i + 1]))
		return ;
	branch->input = 0;
	branch->output = 1;
	while (arr[i])
	{
		if (all->error || (ambiguity(arr[i], arr + i + 1, pre[i + 1], all)))
			return ;
		if (pre && cond_redirect(arr[i]) && !cond_redirect(pre[i]) && ++i)
			continue ;
		check_if_output((char **[2]){arr + i, pre + i}, all, branch, &i);
		if (branch->input == -1 || branch->output == -1)
			return ;
	}
}
