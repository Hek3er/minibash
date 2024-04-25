/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 04:55:58 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/25 08:53:55 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static void	check_append(t_env *tmp, char *key_val, int append, t_all *all)
{
	if (append)
		tmp->value = ft_strjoin(all->tmp_val, key_val, all);
	else
		tmp->value = ft_strdup(key_val, all);
}

void	change_val(t_env **env, char **key_val, int append, t_all *all)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key_val[0]) && key_val[1])
		{
			all->tmp_val = ft_strdup(tmp->value, all);
			// free(tmp->value);
			if (key_val[1])
			{
				check_append(tmp, key_val[1], append, all);
				if (!tmp->value)
				{
					exit_stat(1, 1);
					return ;
				}
			}
			else
				tmp->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
	exit_stat(0, 1);
}
