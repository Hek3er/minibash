/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:53:25 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/23 04:32:59 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static int	is_there_n(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	handle_arg(char **arg, int *flag, t_all *all, int *i)
{
	if (arg[*i][0] == '-')
	{
		if (arg[*i][1] == 'n' && is_there_n(arg[*i]))
		{
			*flag = 1;
			(*i)++;
			return (1);
		}
	}
	if (arg[*i][0] == '$' && arg[*i][1] == '?')
	{
		ft_write(ft_itoa(exit_stat(0, 0), all), 1, 0);
		ft_write(" ", 1, 0);
		exit_stat(0, 1);
		(*i)++;
		return (1);
	}
	if (arg[*i])
	{
		ft_write(arg[*i], 1, 0);
		if (arg[*i] && arg[*i + 1])
			ft_write(" ", 1, 0);
	}
	return (0);
}

int	echo(t_all *all, char **arg)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (all->error)
		return (1);
	if (!arg[i])
	{
		ft_write("\n", 1, 0);
		exit_stat(0, 1);
		return (0);
	}
	while (arg[i])
	{
		if (handle_arg(arg, &flag, all, &i))
			continue ;
		i++;
	}
	if (flag == 0)
		ft_write("\n", 1, 0);
	exit_stat(0, 1);
	return (0);
}
