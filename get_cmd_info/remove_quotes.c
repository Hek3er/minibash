/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:56:01 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/08 10:57:21 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static int	str_length_without_quotes(char *str)
{
	t_check_quote	c_q;
	int				i;
	int				size;

	c_q = (t_check_quote){0};
	size = 0;
	i = 0;
	while (str[i])
	{
		check_quotes(str[i], &c_q);
		if (cond_q(c_q) && ((str[i] == '"' && c_q.is_dq) || \
		(str[i] == '\'' && c_q.is_sq)))
		{
			i++;
			continue ;
		}
		if (!cond_q(c_q) && str[i] != '"' && str[i] != '\'')
			size++;
		if (cond_q(c_q) && !((str[i] == '"' && c_q.is_dq) || \
		(str[i] == '\'' && c_q.is_sq)))
			size++;
		i++;
	}
	return (size);
}

static void	clone_to_new_str(char *src, char *dst, t_check_quote c_q)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (src[i])
	{
		check_quotes(src[i], &c_q);
		if (cond_q(c_q) && ((src[i] == '"' && c_q.is_dq) || \
		(src[i] == '\'' && c_q.is_sq)))
		{
			i++;
			continue ;
		}
		if ((!cond_q(c_q) && src[i] != '"' && src[i] != '\'') || \
		(cond_q(c_q) && !((src[i] == '"' && c_q.is_dq) || \
		(src[i] == '\'' && c_q.is_sq))))
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
}

void	remove_quotes(char **str, t_all *all)
{
	int				str_len;
	char			*new_str;

	while (str && *str)
	{
		str_len = str_length_without_quotes(*str);
		new_str = ft_malloc(str_len + 1, 0, all);
		if (!new_str)
			return ;
		clone_to_new_str(*str, new_str, (t_check_quote){0});
		*str = new_str;
		str ++;
	}
}
