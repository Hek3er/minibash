/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:41:11 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/08 15:56:48 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	check_env(char *next_str, t_all *all)
{
	char	*env;

	env = ft_strdup(next_str, all);
	get_environment(all, &env);
	if (env && *env)
		return (1);
	else
		return (0);
}

static void	get_env_rem_quotes(t_all *all, char **env_arr)
{
	get_environment(all, env_arr);
	remove_quotes(env_arr, all);
}

int	ambiguity(char *str, char **next_str, char *pre, t_all *all)
{
	char	**arr;
	char	**check_wildcard;
	char	*env_arr[2];

	if (!(cond_oper(str, INPUT) || cond_oper(str, OUTPUT) || \
	cond_oper(str, APPEND)))
		return (0);
	check_wildcard = get_wildcard((char *[]){*next_str, NULL}, all);
	if (!check_env(*next_str, all) || (check_wildcard[0] && check_wildcard[1]))
		return (all->error = "Minibash: ambiguous redirect", \
		exit_stat(1, 1), 1);
	arr = split_by_space(*next_str, all, 0);
	if (arr && arr[0])
		*next_str = arr[0];
	if (arr && arr[0] && arr[1])
		return (all->error = "Minibash: ambiguous redirect", \
		exit_stat(1, 1), 1);
	env_arr[0] = pre;
	env_arr[1] = NULL;
	get_env_rem_quotes(all, env_arr);
	arr = split_by_space(pre, all, 0);
	if (arr && (arr[0] && arr[1]))
		return (all->error = "Minibash: ambiguous redirect", \
		exit_stat(1, 1), 1);
	return (0);
}
