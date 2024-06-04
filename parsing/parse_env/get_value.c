/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:19:57 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/04 15:35:13 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

char	*get_value(t_env *env, char *key, t_all *all)
{
	t_env	*tmp;

	if (!env || !key)
		return (NULL);
	// if (key[0] == '\\')
	// {
	// 	// printf("key : %s\n", key);
	// 	all->t_val = key;
	// 	all->t_val2 = ft_strjoin("'", all->t_val + 1, all);
	// 	key = ft_strjoin(all->t_val2, "'", all);
	// 	return (key);
	// }
	tmp = env;
	while (tmp)
	{
		if (!tmp->key)
		{
			tmp = tmp->next;
			continue ;
		}
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->value && tmp->value[0] == '\\')
				all->expand_flag = 1;
			// printf("key: %s, value : %s\n", tmp->key, tmp->value);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
