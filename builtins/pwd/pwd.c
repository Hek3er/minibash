/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:51:24 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/14 16:37:43 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

int	pwd(t_all *all)
{
	t_env	*tmp;
	char	*cwd;

	cwd = ft_malloc(sizeof(char) * PATH_MAX, 0, all);
	if (!cwd)
		return (0);
	tmp = all->env;
	while (tmp && tmp->value)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			printf("%s\n", tmp->value);
			exit_stat(0, 1);
			return (1);
		}
		tmp = tmp->next;
	}
	printf("%s\n", getcwd(cwd, PATH_MAX));
	exit_stat(0, 1);
	return (1);
}
