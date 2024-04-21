/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:55:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/21 11:38:50 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	delim_check(char c, int i)
{
	if (i == 0 && (c == '-' || (c >= '0' && c <= '9')))
		return (0);
	if (is_white_space(c))
		return (0);
	if (c == '$' && i == 0)
		return (1);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || \
	(c >= '0' && c <= '9') || c == '_' || c == '-')
		return (1);
	return (0);
}

static int	my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && delim_check(str[i], i))
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
	// printf("%d\n", key_len);
	key = ft_malloc(key_len + 1, 0, all);
	if (!key)
		return (NULL);
	while (str[j] && i < key_len)
		key[i++] = str[j++];
	key[i] = '\0';
	//to change----------------------------------
	env = get_value(all->env, key+1);
	//--------------------------------------------
	return (env);
}

static char	*add_env(char *str, int i, t_all *all)
{
	char 	*new_str;
	char	*env;
	int		keylen;
	int		j;
	int		k;

	j = 0;
	k = 0;
	keylen = my_strlen(str + i);
	if (keylen == 1)
		return (str);
	env = ft_getenv(str, i, all);
	new_str = ft_malloc(ft_strlen(env) + ft_strlen(str) - keylen + 1, 0, all);
	if (!new_str)
		return (NULL);
	while (j < i)
		new_str[k++] = str[j++];
	while (env && *env)
		new_str[k++] = *(env++);
	j+= keylen;
	while (str[j])
		new_str[k++] = str[j++];
	new_str[k] = '\0';
	return (new_str);
}

void	get_environment(t_all *all, char **s)
{
	int				i;
	t_check_quote	c_q;
	char			c;
	char			y;
	char			next_c;

	c_q = (t_check_quote){0};
	i = 0;
	y = 0;
	while ((*s)[i])
	{
		c = (*s)[i];
		next_c = (*s)[i + 1];
		check_quotes(c, &c_q);
		// printf("{%d %c}\n", delim_check(c, i),c);
		if (c == ' ' || c == '"')
			y = -1;
		if (c == '$' && delim_check(c, y) && next_c != '?' && !is_white_space(next_c) \
		&& !c_q.is_sq)
			*s = add_env((*s), i, all);
		i++;
		y++;
	}
	// printf("%s\n", *s);
}
