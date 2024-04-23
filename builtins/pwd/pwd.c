/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:51:24 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/23 05:38:25 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

int	pwd(t_all *all)
{
	t_env	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			printf("%s\n", tmp->value);
			exit_stat(0, 1);
			return (1);
		}
		tmp = tmp->next;
	}
	exit_stat(0, 1);
	return (1);
}
