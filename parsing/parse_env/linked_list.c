/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:22:28 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/25 12:17:40 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

void	malloc_error(void)
{
	ft_write("Malloc error", 2, 1);
	exit(1);
}

t_env	*create_node(char *key, char *value, t_all *all)
{
	t_env	*env;

	env = ft_malloc(sizeof(t_env), 0, all);
	if (!env)
		malloc_error();
	env->key = ft_strdup(key, all);
	if (!env->key)
		malloc_error();
	if (value)
	{
		env->value = ft_strdup(value, all);
		if (!env->value)
			malloc_error();
	}
	else if (!value)
		env->value = NULL;
	return (env->next = NULL, env);
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
