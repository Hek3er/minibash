/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 04:13:08 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/15 22:04:20 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static void	swap(t_env *tmp)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = tmp->key;
	tmp->key = tmp->next->key;
	tmp->next->key = temp_key;
	temp_value = tmp->value;
	tmp->value = tmp->next->value;
	tmp->next->value = temp_value;
}

static t_env	*sort_export(t_env *env)
{
	t_env	*tmp;
	char	*temp_key;
	char	*temp_value;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp = env;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				swap(tmp);
				swapped = 1;
			}
			tmp = tmp->next;
		}
	}
	return (env);
}

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = sort_export(env);
	while (tmp)
	{
		if (!tmp->value)
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	exit_stat(0, 1);
}