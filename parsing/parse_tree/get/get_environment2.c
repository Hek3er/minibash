/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:31:24 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/28 10:11:52 by ealislam         ###   ########.fr       */
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
	if (str[i] && i < 1 && !delim_check(str[i], i))
		i++;
	// printf("cccc %c\n", str[i]);
	// if (i == 1 && str[i] == '"')
    //     return (0);
	// if (str[i] == '\'' && str[i] == '"')
    //     return (i);
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
	if (ft_strcmp(key + 1, "\"") == 0) //  ghir improvisit idon't know wesh 5asert chi la3ba a5ra
		return ("");
	else if (ft_strcmp(key + 1, "\'") == 0)
		return ("");
	env = get_value(all->env, key + 1);
	return (env);
}

char	*add_env(char *str, int *i, t_all *all, t_check_quote *c_q)
{
	char	*new_str;
	char	*env;
	int		keylen;
	int		j;
	int		k;

	j = 0;
	k = 0;
	keylen = my_strlen(str + *i);
	if (keylen == 1)
		return (str);
	env = ft_getenv(str, *i, all);
	new_str = ft_malloc(ft_strlen(env) + (ft_strlen(str) - keylen + 1 - (c_q->is_dq)), 0, all);
	if (!new_str)
		return (NULL);
	// while (j < *(i) - c_q->is_dq)
	while (j < *(i) - c_q->is_dq)
		new_str[k++] = str[j++];
	while (env && *env)
		new_str[k++] = *(env++);
	// if (c_q->is_dq)
	// 	j++;
	if (keylen == 0 || c_q->is_dq)
		j++;
	j += keylen;
	while (str[j])
		new_str[k++] = str[j++];
	new_str[k] = '\0';
	if (*i)
		(*i)--;
	return (new_str);
}
