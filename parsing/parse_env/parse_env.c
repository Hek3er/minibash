/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:05:40 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/15 14:24:29 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static void	copy_key(char **env, t_var *var, t_all *all)
{
	var->tmp_key = ft_substr(env[var->i], 0, var->j, all);
	if (!var->tmp_key)
	{
		ft_write("Malloc error", 2, 1);
		exit(2);
	}
	var->rem = var->j + 1;
}

static void	set_empty_env(t_env **head, t_all *all, t_var *var)
{
	append_node(head, "SHLVL", "1", all);
	append_node(head, "PWD", getcwd(NULL, 0), all);
	var->str = ft_strjoin(getcwd(NULL, 0), "/minibash", all);
	append_node(head, "_", var->str, all);
	append_node(head, "PATH", "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin", \
	all);
}

static int	get_lenght_up_to_equal(char *s)
{
	int	j;

	j = 0;
	while (s[j] != '=')
		j++;
	return (j);
}

t_env	*parse_env(char **env, t_all *all)
{
	t_var	var;
	t_env	*head;

	head = NULL;
	var.i = 0;
	if (!env[0])
		return (set_empty_env(&head, all, &var), head);
	while (env[var.i])
	{
		var.j = get_lenght_up_to_equal(env[var.i]);
		if (env[var.i][var.j] == '=')
			copy_key(env, &var, all);
		var.j = ft_strlen(env[var.i]);
		var.tmp_val = ft_substr(env[var.i], var.rem, var.j - var.rem, all);
		if (!var.tmp_val)
			(ft_write("Malloc error", 2, 1), exit(2));
		if (!ft_strcmp(var.tmp_key, "SHLVL"))
			append_node(&head, var.tmp_key, \
			ft_itoa(ft_atoi(var.tmp_val) + 1, all), all);
		else
			append_node(&head, var.tmp_key, var.tmp_val, all);
		var.i++;
	}
	return (head);
}
