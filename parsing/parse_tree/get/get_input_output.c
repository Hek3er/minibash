/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:47:29 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/15 14:09:53 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	ambiguity(char *str, char **next_str, char *pre, t_all *all)
{
	char	**arr;
	int		is_diffrent;

	is_diffrent = ft_strcmp(*next_str, pre);
	if (!(cond_oper(str, INPUT) || cond_oper(str, OUTPUT) || \
	cond_oper(str, APPEND)))
		return (0);
	arr = split_by_space(*next_str, all);
	if (arr && arr[0])
		*next_str = arr[0];
	if (arr && arr[1])
		return (all->error = "Minibash: ambiguous redirect", \
		exit_stat(1, 1), 1);
	get_environment(all, &pre);
	arr = split_by_space(pre, all);
	if (arr && arr[1])
		return (all->error = "Minibash: ambiguous redirect", \
		exit_stat(1, 1), 1);
	return (0);
}

static void	move_cmd(char **arr[2])
{
	int	i;

	i = 0;
	while (arr[0][i])
	{
		if (!arr[0][i + 1])
		{
			arr[0][i] = NULL;
			arr[1][i] = NULL;
		}
		arr[0][i] = arr[0][i + 1];
		arr[1][i] = arr[1][i + 1];
		i++;
	}
}

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

static int	check_if_output(char **arr_pre[2], int *pre_fd, int ex, t_all *all)
{
	int	cnd_oper_type;
	int	oper_size;
	int	fd;

	fd = ex;
	if (ex)
		cnd_oper_type = (cond_oper(*arr_pre[0], OUTPUT) || \
		cond_oper(*arr_pre[0], APPEND));
	else
		cnd_oper_type = cond_oper(*arr_pre[0], INPUT);
	oper_size = cond_redirect(*arr_pre[0]);
	if (oper_size && cnd_oper_type)
		fd = open_file(arr_pre[0][1], oper_size, ex, all);
	if (*pre_fd != fd && *pre_fd != ex && fd != ex)
		ft_open(NULL, 0, NULL, *pre_fd);
	if (fd > ex || cond_oper(*arr_pre[0], H_DOC))
	{
		move_cmd(arr_pre);
		move_cmd(arr_pre);
	}
	return (fd);
}

int	get_input_output(char **arr, int expected, char **pre, t_all *all)
{
	int	i;
	int	fd;
	int	final_fd;

	i = 0;
	final_fd = expected;
	if ((!arr) || (arr[i] && (cond_oper(arr[i], INPUT) || \
	cond_oper(arr[i], OUTPUT) || cond_oper(arr[i], APPEND)) && !arr[i + 1]))
		return (expected);
	while (arr[i] && arr[i + 1])
	{
		if (all->error || (ambiguity(arr[i], arr + i + 1, pre[i + 1], all)))
			return (expected);
		if (pre && cond_redirect(arr[i]) && !cond_redirect(pre[i]) && ++i)
			continue ;
		fd = check_if_output((char **[2]){arr + i, pre + i}, &final_fd, \
		expected, all);
		if (fd == -1)
			return (expected);
		if (fd != expected)
			final_fd = fd;
		if (fd == expected)
			i++;
	}
	return (final_fd);
}
