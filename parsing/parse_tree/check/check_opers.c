/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:42:22 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/19 00:39:00 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	compare_oper(char *str, int *i, int oper[2])
{
	int	oper_i;

	if(oper[0])
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
		return ((*i)++,oper[oper_i] = 2, 2);
	if (cond_oper(str, PIPE))
		return (oper[oper_i] = 2, 2);
	return (0);
}

void	check_opers(char *str, t_all *all)
{
	int				i;
	int				oper[3];
	t_check_quote	c_q;

	i = 0;
	c_q = (t_check_quote){0};
	oper[0] = 0, oper[1] = 0, oper[2] = 0;
	if (cond_oper(str, OR) || cond_oper(str, AND) || cond_oper(str, PIPE))
	{
		(all->error = "minibash: syntax error", exit_stat(258, 1));
		return;
	}
	while (str[i])
	{
		check_quotes(str[i], &c_q);
		if (str[i] == ' ' && ++i)
			continue ;
		if (!compare_oper(str + i, &i, oper) || cond_q(c_q))
			(oper[0] = 0, oper[1] = 0);
		if (oper[2] || (oper[1] && oper[0] - oper[1] <= 0))
			(all->error = "minibash: syntax error", exit_stat(258, 1));
		i++;
	}
	if (oper[0] || oper[1])
		(all->error = "minibash: syntax error", exit_stat(258, 1));
}
