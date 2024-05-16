/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 04:52:58 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/14 15:55:32 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

int	check_key(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && !ft_strncmp(tmp->key, key, ft_strlen(tmp->key)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
