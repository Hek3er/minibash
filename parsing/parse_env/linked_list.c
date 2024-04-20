/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:22:28 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/19 05:41:55 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

t_env	*create_node(char *key, char *value, t_all *all)
{
	t_env	*env;

	env = ft_malloc(sizeof(t_env), 0, all);
	if (!env)
	{
		ft_write("Malloc error", 2, 1);
		exit(2);
	}
	env->key = ft_strdup(key, all);
	if (!env->key)
	{
		ft_write("Malloc error", 2, 1);
		exit(3);
	}
	if (value)
	{
		env->value = ft_strdup(value, all);
		if (!env->value)
		{
			ft_write("Malloc error", 2, 1);
			exit(4);
		}
	}
	else if (!value)
		env->value = NULL;
	env->next = NULL;
	return (env);
}

void	append_node(t_env **head, char *key, char *value, t_all *all)
{
	t_env	*new_node;
	t_env	*last_node;

	new_node = create_node(key, value, all);
	if (!head || !(*head))
	{
		(*head) = new_node;
		return ;
	}
	last_node = (*head);
	while (last_node->next != NULL)
	{
		last_node = last_node->next;
	}
	last_node->next = new_node;
}
