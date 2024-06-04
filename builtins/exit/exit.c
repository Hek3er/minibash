/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:19:59 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/04 16:26:26 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '+')
		i++;
	if (str && str[i] == '-')
		return (2);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (ft_strlen(str) > 19 || ((ft_strlen(str) == 19 && str[18] > '7')))
		return (0);
	return (1);
}

void	ft_exit(char **cmd, t_all *all)
{
	int	exit_st;
	int	i;

	exit_st = exit_stat(0, 0);
	i = 0;
	while (cmd && cmd[i])
		i++;
	ft_write("exit", 2, 1);
	if (cmd && cmd[1])
	{
		if (ft_isnum(cmd[1]) == 0 || ft_isnum(cmd[1]) == 2)
		{
			exit_st = 255;
			if (ft_isnum(cmd[1]) == 0)
			{
				ft_write("minibash: exit: ", 2, 0);
				ft_write(cmd[1], 2, 0);
				ft_write(": numeric argument required", 2, 1);
			}		
		}
		else if (i > 2)
		{
			ft_write("minibash: exit: too many arguments", 2, 1);
			exit_st = 1;
			exit_stat(1, 1);
			return ;
		}
		else
			exit_st = ft_atoi(cmd[1]);
	}
	remove_docs(all);
	ft_open(NULL, 0, NULL, 1);
	ft_malloc(0, 1, NULL);
	exit(exit_st);
}
