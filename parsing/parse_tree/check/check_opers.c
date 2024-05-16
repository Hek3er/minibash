/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:42:22 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/15 14:03:25 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	compare_oper(char *str, int *i, int oper[2])
{
	int	oper_i;

	if (oper[0])
		oper_i = 1;
	else if (oper[1])
		oper_i = 2;
	else
		oper_i = 0;
	if (cond_oper(str, H_DOC) || cond_oper(str, APPEND))
		return ((*i)++, oper[oper_i] = 1, 1);
	if (cond_oper(str, INPUT) || cond_oper(str, OUTPUT))
		return (oper[oper_i] = 1, 1);
	if (cond_oper(str, OR) || cond_oper(str, AND))
		return ((*i)++, oper[oper_i] = 2, 2);
	if (cond_oper(str, PIPE))
		return (oper[oper_i] = 2, 2);
	return (0);
}

static void	fill_arr_with_zero(int arr[])
{
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 0;
}

static void	error_and_status(t_all *all)
{
	all->error = "minibash: syntax error";
	exit_stat(258, 1);
}

void	check_opers(char *str, t_all *all)
{
	int				i;
	int				oper[3];
	t_check_quote	c_q;

	i = 0;
	c_q = (t_check_quote){0};
	fill_arr_with_zero(oper);
	if (cond_oper(str, OR) || cond_oper(str, AND) || cond_oper(str, PIPE))
	{
		error_and_status(all);
		return ;
	}
	while (str[i])
	{
		check_quotes(str[i], &c_q);
		if (is_white_space(str[i]) && ++i)
			continue ;
		if (!compare_oper(str + i, &i, oper) || cond_q(c_q))
			fill_arr_with_zero(oper);
		if (oper[2] || (oper[1] && oper[0] - oper[1] <= 0))
			error_and_status(all);
		i++;
	}
	if (oper[0] || oper[1])
		error_and_status(all);
}
