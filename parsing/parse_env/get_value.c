/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:19:57 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/27 20:28:59 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

char	*get_value(t_env *env, char *key, t_all *all)
{
	t_env	*tmp;

	if (!env || !key)
		return (NULL);
	if (key[0] == '\\') {
		char *tmp = key;
		char *tmp2 = ft_strjoin("'", tmp + 1, all);
		key = ft_strjoin(tmp2, "'", all);
		printf("key : %s\n", key);
		return key;
	}
	tmp = env;
	while (tmp)
	{
		if (!tmp->key)
		{
			tmp = tmp->next;
			continue ;
		}
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
