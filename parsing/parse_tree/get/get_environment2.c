/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:31:24 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/11 19:37:31 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	delim_check(char c, int i)
{
	if (i == 0)
		return (1);
	if (i == 1 && (is_dash(c) || is_num(c)))
		return (0);
	if (is_alpha(c) || is_num(c) || c == '_')
		return (1);
	return (0);
}

static int	my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && delim_check(str[i], i))
		i++;
	if (i == 1 && (str[i] == '"' || str[i] == '\''))
		return (0);
	if (str[i] && i <= 1 && !delim_check(str[i], i))
		i++;
	return (i);
}

static char	*ft_getenv(char *str, int j, t_all *all)
{
	char	*key;
	int		key_len;
	char	*env;
	int		i;

	i = 0;
	key_len = my_strlen(str + j);
	key = ft_malloc(key_len + 1, 0, all);
	if (!key)
		return (NULL);
	while (str[j] && i < key_len)
		key[i++] = str[j++];
	key[i] = '\0';
	if (key_len == 0)
		return (NULL);
	env = get_value(all->env, key + 1, all);
	return (env);
}

char	*add_env2(char *str, char *env, int *i, t_all *all)
{
	char	*new_str;

	new_str = ft_malloc(ft_strlen(env) + ft_strlen(str) + \
	(all->is_outside_dq * 2) - all->keylen + 1, 0, all);
	if (!new_str)
		return (NULL);
	while (all->j < *(i))
		new_str[all->k++] = str[all->j++];
	if (all->is_outside_dq)
		new_str[all->k++] = '"';
	while (env && *env)
		new_str[all->k++] = *(env++);
	if (all->is_outside_dq)
		new_str[all->k++] = '"';
	if (all->keylen == 0)
		all->j++;
	all->j += all->keylen;
	while (str[all->j])
		new_str[all->k++] = str[all->j++];
	new_str[all->k] = '\0';
	return (new_str);
}

char	*add_env(char *str, int *i, t_all *all, t_check_quote c_q)
{
	char	*new_str;
	char	*env;

	all->j = 0;
	all->k = 0;
	all->keylen = my_strlen(str + *i);
	if (all->keylen == 1)
		return (str);
	env = ft_getenv(str, *i, all);
	if (all->expand_flag)
		env++;
	all->is_outside_dq = 1;
	if (c_q.is_dq || env == NULL || !all->add_quotes_to_env)
		all->is_outside_dq = 0;
	if (cond_oper(env, NONE))
		all->is_outside_dq = 1;
	new_str = add_env2(str, env, i, all);
	(*i)--;
	if (all->expand_flag)
	{
		(*i) += 2;
		all->expand_flag = 0;
	}
	return (new_str);
}
