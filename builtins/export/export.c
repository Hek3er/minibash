/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 00:57:51 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/06 17:03:30 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static int	split_key_val(int i, char *arg, char **key_val, t_all *all)
{
	all->append = 0;
	if (arg[i - 1] == '+' && ft_isunder_alpha(arg[i - 2]))
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

char	**parse_export(char **arg, int k, t_all *all)
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

int	parse_key(char **key_val, t_all *all)
{
	int	i;

	i = 1;
	if (!ft_isunder_alpha(key_val[0][0]))
		return (all->tmp = \
		ft_strjoin(key_val[0], "': not a valid undentifier", all), \
		exit_stat(1, 1), 1);
	while (key_val[0][i] && i < ft_strlen(key_val[0]) - 1)
	{
		if (!ft_isunder_alpha(key_val[0][i]))
			return (all->tmp = \
			ft_strjoin(key_val[0], "': not a valid undentifier", \
			all), exit_stat(1, 1), 1);
		i++;
	}
	i = ft_strlen(key_val[0]) - 1;
	if (!(ft_isalnum(key_val[0][i])) && !(key_val[0][i] == '+'))
		return (all->tmp = \
		ft_strjoin(key_val[0], "': not a valid undentifier", all), \
		exit_stat(1, 1), 1);
	return (0);
}

void	export(t_all *all, t_env *env, char **arg)
{
	char	**key_val;
	int		k;

	k = 1;
	all->tmp = NULL;
	key_val = NULL;
	if (!arg[k])
	{
		print_export(env);
		return ;
	}
	while (arg[k])
	{
		printf("arg[k] = %s\n", arg[k]);
		handle_export_arg(key_val, arg, k, all);
		k++;
	}
	if (all->tmp)
	{
		all->error = ft_strjoin("minibash: export: `", all->tmp, all);
		return ;
	}
	exit_stat(0, 1);
}
