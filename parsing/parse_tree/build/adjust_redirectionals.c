/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_redirectionals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:20:13 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/15 13:54:28 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static char	*append_space(char *str, int i, int oper_size, t_all *all)
{
	int		j;
	char	*new_str;

	j = 0;
	new_str = ft_malloc(ft_strlen(str) + 1 + oper_size, 0, all);
	if (!new_str)
		return (NULL);
	while (j < i)
	{
		new_str[j] = str[j];
		j++;
	}
	new_str[j] = ' ';
	j++;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);
}

char	*adjust_redirectionals(char *str, t_all *all)
{
	int				i;
	int				oper_size;
	t_check_quote	c_q;

	i = 0;
	c_q = (t_check_quote){0};
	while (str[i])
	{
		check_quotes(str[i], &c_q);
		oper_size = cond_redirect(str + i);
		if (!cond_q(c_q) && i != 0 && oper_size && str[i - 1] != ' ' && i++)
			str = append_space(str, i - 1, oper_size, all);
		if (!cond_q(c_q) && oper_size && str[i + oper_size] != ' ')
			str = append_space(str, i + oper_size, oper_size, all);
		if (str == NULL)
			return (NULL);
		if (oper_size)
			i += oper_size;
		else
			i++;
	}
	return (str);
}
