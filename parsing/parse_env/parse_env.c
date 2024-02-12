/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:05:40 by azainabi          #+#    #+#             */
/*   Updated: 2024/02/12 07:13:07 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static void	copy_key(char **env, t_var *var)
{
	var->tmp_key = ft_substr(env[var->i], 0, var->j);
	if (!var->tmp_key)
		error_exit("Error substr", 2);
	var->rem = var->j + 1;
}

t_env	*parse_env(char **env)
{
	t_var	var;
	t_env	*head;

	head = NULL;
	var.i = 0;
	while (env[var.i])
	{
		var.j = 0;
		while (env[var.i][var.j] != '=')
			var.j++;
		if (env[var.i][var.j] == '=')
			copy_key(env, &var);
		var.j = 0;
		while (env[var.i][var.j])
			var.j++;
		var.tmp_val = ft_substr(env[var.i], var.rem, var.j - var.rem);
		if (!var.tmp_val)
			error_exit("Error substr", 2);
		append_node(&head, var.tmp_key, var.tmp_val);
		free(var.tmp_key);
		free(var.tmp_val);
		var.i++;
	}
	return (head);
}
