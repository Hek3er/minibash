/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:53:25 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/18 00:28:19 by azainabi         ###   ########.fr       */
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

int	echo(t_all *all, char **arg)
{
	int	i;
	int	j;
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
		if (arg[i][0] == '-')
		{
			if (arg[i][1] == 'n' && is_there_n(arg[i]))
			{
				flag = 1;
				i++;
				continue ;
			}
		}
		if (arg[i][0] == '$' && arg[i][1] == '?')
		{
			ft_write(ft_itoa(exit_stat(0, 0), all), 1, 0); // might cause a leak
			ft_write(" ", 1, 0);
			exit_stat(0, 1);
			i++;
			continue ;
		}
		if (arg[i])
		{
			ft_write(arg[i], 1, 0);
			if (arg[i] && arg[i + 1])
				ft_write(" ", 1, 0);
		}
		i++;
	}
	if (flag == 0)
		ft_write("\n", 1, 0);
	exit_stat(0, 1);
	return (0);
}
