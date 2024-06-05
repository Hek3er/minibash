/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:55:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/05 17:26:02 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static void	add_str_to_str(int *i, char *src, char *dst)
{
	dst[*i] = src[*i];
	(*i)++;
}

static void	handle_question_mark(int i, char **str, t_all *all)
{
	char	*new_str;
	char	*status;
	int		j;
	int		length;

	j = 0;
	status = ft_itoa(exit_stat(0, 0), all);
	length = ft_strlen(*str) + ft_strlen(status) - 1;
	new_str = ft_malloc(length, 0, all);
	if (!new_str)
		return ;
	while (j < i)
		add_str_to_str(&j, *str, new_str);
	j = 0;
	while (j < ft_strlen(status))
		add_str_to_str(&j, status, new_str + i);
	while ((*str)[i + 2])
		add_str_to_str(&i, (*str) + 2, new_str + j);
	*str = new_str;
	(*str)[length - 1] = '\0';
}

static int	delim_check(int *i, int y, char **str, t_all *all)
{
	char	c;
	char	next_c;

	c = (*str)[*i];
	next_c = (*str)[(*i) + 1];
	if (next_c == '?')
	{
		handle_question_mark(*i, str, all);
		return (0);
	}
	// printf("%c %c\n", c, next_c);
	if (!(is_alpha(next_c) || is_num(next_c) || next_c != '"' || next_c != '\''))
		return (0);
	if (c == '$' && y >= 0)
		return (1);
	return (1);
}

static int	check_dollar_in_q(t_check_quote *c_q, int i, char **str)
{
	char	next_c;

	next_c = (*str)[i + 1];
	if (c_q->is_dq)
	{
		if (is_alpha(next_c) || is_num(next_c))
			return (1);
		return (0);
	}
	return (1);
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
	// printf("all->exfl : %d\n", all->expand_flag);
	// all->expand_flag = 0;
	while ((*s) && (*s)[i])
	{
		c = (*s)[i];
		next_c = (*s)[i + 1];
		check_quotes(c, &c_q);
		if (c == ' ' || c == '"' || c == '\'')
			y = -1;
		if (c == '$' && !c_q.is_sq && delim_check(&i, y, s, all) && \
		!is_white_space(next_c) && check_dollar_in_q(&c_q, i, s))
			*s = add_env((*s), &i, all, c_q);
		if (i >= 0 && (*s)[i] == '\0')
			break ;
		// all->expand_flag = 0;
		i++;
		y++;
	}
}
