/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 00:57:51 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/19 06:14:44 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static int	split_key_val(int i, char *arg, char **key_val, t_all *all)
{
	all->append = 0;
	if (arg[i - 1] == '+')
	{
		key_val[0] = ft_substr(arg, 0, i - 1, all);
		all->append = 1;
	}
	else
		key_val[0] = ft_substr(arg, 0, i, all);
	if (!key_val[0])
		return (0);
	key_val[1] = ft_substr(arg, i + 1, ft_strlen(arg) - i - 1, all);
	if (!key_val[1])
		return (0);
	return (1);
}

static char	**parse_export(char **arg, int k, t_all *all)
{
	char	**key_val;
	int		i;

	i = 0;
	key_val = ft_malloc(sizeof(char *) * 2, 0, all);
	if (!key_val)
		return (NULL);
	while (arg[k][i] != '=' && arg[k][i] != 0)
		i++;
	if (arg[k][i] == '=')
	{
		if (!split_key_val(i, arg[k], key_val, all))
			return (NULL);
	}
	else
	{
		key_val[0] = ft_strdup(arg[k], all);
		if (!key_val[0])
			return (NULL);
		key_val[1] = NULL;
	}
	return (key_val);
}

static void	parse_key(char **key_val, t_all *all)
{
	int	i;

	i = 1;
	if (!ft_isunder_alpha(key_val[0][0]))
	{
		all->tmp = ft_strjoin(key_val[0], "': not a valid undentifier", all);
		exit_stat(1, 1);
		return ;
	}
	while (key_val[0][i] && i < ft_strlen(key_val[0]) - 1)
	{
		if (!ft_isunder_alpha(key_val[0][i]))
		{
			all->tmp = ft_strjoin(key_val[0], "': not a valid undentifier", all);
			exit_stat(1, 1);
			return ;
		}
		i++;
	}
	i = ft_strlen(key_val[0]) - 1;
	if (!(ft_isalnum(key_val[0][i])) && !(key_val[0][i] == '+'))
	{
		all->tmp = ft_strjoin(key_val[0], "': not a valid undentifier", all);
		exit_stat(1, 1);
		return ;
	}
}

void	export(t_all *all, t_env *env, char **arg)
{
	char	**key_val;
	int		k;

	k = 1;
	all->tmp = NULL;
	if (!arg[k])
	{
		print_export(env);
		return ;
	}
	while (arg[k])
	{
		key_val = parse_export(arg, k, all);
		if (!key_val)
			return ;
		parse_key(key_val, all);
		if (!check_key(env, key_val[0]))
			append_node(&env, key_val[0], key_val[1], all);
		else
			change_val(&env, key_val, all->append, all);
		k++;
	}
	if (all->tmp)
	{
		all->error = ft_strjoin("minibash: export: `", all->tmp, all);
		return ;
	}
	exit_stat(0, 1);
}
