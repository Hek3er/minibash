/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_parantheses.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:57:04 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/15 14:11:19 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	check_str(char *s, t_all *all)
{
	int				i;
	int				p_i;
	t_check_quote	c_q;

	i = 0;
	p_i = 0;
	c_q = (t_check_quote){0};
	while (is_white_space(s[i]))
		i++;
	if (s[i] != '(')
		return (all->error = "minibash: syntax error", exit_stat(258, 1), 1);
	while (s[i])
	{
		(check_parentheses(s[i], &p_i), check_quotes(s[i], &c_q));
		if (s[i] == ')' && !cond_q(c_q) && !p_i)
			break ;
		i++;
	}
	i++;
	while (is_white_space(s[i]))
		i++;
	if (s[i] && !(cond_oper(s, PIPE) || cond_oper(s, AND) || \
	cond_oper(s, OR)))
		return (all->error = "minibash: syntax error", exit_stat(258, 1), 1);
	return (0);
}

static int	get_para_size(char *str, t_all *all, t_check_quote c_q)
{
	int				i;
	int				size;
	int				p_i;

	i = 0;
	size = 0;
	p_i = 0;
	while (is_white_space(str[i]))
		i++;
	i++;
	while (str[i])
	{
		check_parentheses(str[i], &p_i);
		check_quotes(str[i], &c_q);
		i++;
		size++;
		if (str[i] == ')' && !cond_q(c_q) && !p_i)
			break ;
	}
	if (p_i)
	{
		all->error = "minibash: syntax error";
		exit_stat(258, 1);
	}
	return (size);
}

char	*split_by_parantheses(char *str, t_all *all)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	check_str(str, all);
	if (all->error)
		return (NULL);
	new_str = ft_malloc(get_para_size(str, all, (t_check_quote){0}) + 1, \
	0, all);
	if (!new_str)
		return (NULL);
	while (is_white_space(str[i]))
		i++;
	i++;
	while (j < get_para_size(str, all, (t_check_quote){0}))
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);
}
