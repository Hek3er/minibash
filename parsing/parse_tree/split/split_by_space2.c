/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_space2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:24:35 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/08 10:43:58 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	str_size(t_split *all_s, int s_i)
{
	int		i;
	int		size;
	char	*str;

	i = s_i;
	size = 0;
	str = all_s->str;
	all_s->c_q = (t_check_quote){0};
	while (str[i])
	{
		check_quotes(str[i], &(all_s->c_q));
		check_parentheses(str[i], &(all_s->c_p));
		if (cond_space(str, i) && !cond_q(all_s->c_q) && !all_s->c_p)
			return (size);
		if (!cond_jump_quote(str[i], all_s->c_q, all_s->jump_quote))
			size++;
		i++;
	}
	return (size);
}

static void	fill_str(t_split *all_s, char *dst, int *s_i)
{
	int		i;
	char	*s;

	i = *s_i;
	s = all_s->str;
	all_s->c_q = (t_check_quote){0};
	all_s->c_p = 0;
	while (s[i] && (!cond_space(s, i) || (cond_q(all_s->c_q) || all_s->c_p)))
	{
		check_quotes(s[i], &(all_s->c_q));
		check_parentheses(s[i], &(all_s->c_p));
		if (!cond_jump_quote(s[i], all_s->c_q, all_s->jump_quote))
		{
			*dst = s[i];
			dst++;
		}
		i++;
		(*s_i)++;
	}
	*dst = '\0';
}

static void	add_str_to_arr(t_split *all_s, int *s_i, int arr_i, t_all *all)
{
	all_s->arr[arr_i] = ft_malloc(str_size(all_s, *s_i) + 1, 0, all);
	if (all_s->arr[arr_i] == NULL)
		return ;
	fill_str(all_s, all_s->arr[arr_i], s_i);
	arr_i++;
}

int	split_by_space2(t_split *all_s, t_all *all, int flag, int jump_quote)
{
	int		s_i;
	int		arr_i;

	s_i = 0;
	arr_i = 0;
	all_s->c_q = (t_check_quote){0};
	all_s->jump_quote = jump_quote;
	check_quotes((all_s->str)[s_i], &(all_s->c_q));
	check_parentheses((all_s->str)[s_i], &(all_s->c_p));
	if ((all_s->str)[s_i] && (all_s->str)[s_i] != ' ')
		add_str_to_arr(all_s, &s_i, arr_i++, all);
	while (all_s->str[s_i] != '\0')
	{
		if (!cond_space((all_s->str), s_i) && cond_space((all_s->str), \
		s_i - 1) && !cond_q(all_s->c_q) && !all_s->c_p)
			(add_str_to_arr(all_s, &s_i, arr_i++, all), flag = 1);
		check_quotes((all_s->str)[s_i], &(all_s->c_q));
		check_parentheses((all_s->str)[s_i], &(all_s->c_p));
		if (flag)
			(1 == 1) && (flag = 0, s_i--);
		s_i++;
	}
	return (1);
}
