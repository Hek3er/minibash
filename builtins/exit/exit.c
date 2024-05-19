/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:19:59 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/19 19:13:26 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

void	ft_exit(char **cmd, t_all *all)
{
	int	exit_st;
	int	i;

	exit_st = 0;
	i = 0;
	while (cmd[i])
		i++;
	ft_write("exit", 1, 1);
	if (i > 2)
	{
		ft_write("minibash: exit: too many arguments", 2, 1);
		exit_st = 1;
	}
	if (cmd[1] && i <= 2)
		exit_st = ft_atoi(cmd[1]);
	remove_docs(all);
	ft_open(NULL, 0, NULL, 1);
	ft_malloc(0, 1, NULL);
	exit(exit_st);
}
