/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_space2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:24:35 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/19 06:42:16 by azainabi         ###   ########.fr       */
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
		if (!cond_jump_quote(str[i], all_s->c_q))
			size++;
		i++;
	}
	return (size);
}

static void	fill_str(t_split *all_s, char *dst, int *s_i)
{
	int		i;
	char	*str;

	i = *s_i;
	str = all_s->str;
	all_s->c_q = (t_check_quote){0};
	all_s->c_p = 0;
	while ((str[i] && !cond_space(str, i)) || cond_q(all_s->c_q) || all_s->c_p)
	{
		check_quotes(str[i], &(all_s->c_q));
		check_parentheses(str[i], &(all_s->c_p));
		if (!cond_jump_quote(str[i], all_s->c_q))
		{
			*dst = str[i];
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

int	split_by_space2(t_split *all_s, t_all *all)
{
	int		s_i;
	int		arr_i;
	char	*str;

	s_i = 0;
	arr_i = 0;
	str = all_s->str;
	all_s->c_q = (t_check_quote){0};
	check_quotes(str[s_i], &(all_s->c_q));
	check_parentheses(str[s_i], &(all_s->c_p));
	if (str[s_i] && str[s_i] != ' ')
		add_str_to_arr(all_s, &s_i, arr_i++, all);
	s_i++;
	while (all_s->str[s_i])
	{
		if (!cond_space(str, s_i) && cond_space(str, s_i - 1) && \
		!cond_q(all_s->c_q) && !all_s->c_p)
			add_str_to_arr(all_s, &s_i, arr_i++, all);
		check_quotes(str[s_i], &(all_s->c_q));
		check_parentheses(str[s_i], &(all_s->c_p));
		s_i++;
	}
	return (1);
}
