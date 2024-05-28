/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:31:24 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/28 18:42:27 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	delim_check(char c, int i)
{
	if (i == 0)
		return (1);
	if (i == 1 && (is_dash(c) || is_num(c)))
		return (0);
	if (is_alpha(c) || is_num(c))
		return (1);
	return (0);
}

static int	my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && delim_check(str[i], i))
		i++;
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
	if (ft_strcmp(key + 1, "\"") == 0)
		return ("\"");
	else if (ft_strcmp(key + 1, "\'") == 0)
		return ("\'");
	env = get_value(all->env, key + 1, all);
	return (env);
}

char	*add_env2(char *str, char *env, int *i, t_all *all)
{
	char	*new_str;

	new_str = ft_malloc(ft_strlen(env) + ft_strlen(str) - all->keylen + 1, \
	0, all);
	if (!new_str)
		return (NULL);
	while (all->j < *(i))
		new_str[all->k++] = str[all->j++];
	while (env && *env)
	{
		if (env[0] == '\\' && env[1] == '$')
		{
			env++;
			continue ;
		}
		new_str[all->k++] = *(env++);
	}
	if (all->keylen == 0)
		all->j++;
	all->j += all->keylen;
	while (str[all->j])
		new_str[all->k++] = str[all->j++];
	new_str[all->k] = '\0';
	return (new_str);
}

char	*add_env(char *str, int *i, t_all *all)
{
	char	*new_str;
	char	*env;

	all->j = 0;
	all->k = 0;
	all->keylen = my_strlen(str + *i);
	if (all->keylen == 1)
		return (str);
	if (all->expand_flag)
	{
		env = ft_strdup(str + (*i), all);
		printf("env : %s\n", env);
		if (!env)
			return (NULL);
	}
	else
		env = ft_getenv(str, *i, all);
	new_str = add_env2(str, env, i, all);
	if (*i)
		(*i)--;
	return (new_str);
}
