/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:24:35 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/08 15:53:00 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	count_arr_length(char *s)
{
	int				count;
	t_check_quote	c_q;
	int				c_p;
	int				i;

	count = 0;
	i = 0;
	c_p = 0;
	c_q = (t_check_quote){0};
	check_quotes(s[i], &c_q);
	check_parentheses(s[i], &c_p);
	if (s[i] && s[i] != ' ')
		count++;
	i++;
	while (*s && s[i] && s[i - 1])
	{
		if (!cond_space(s, i) && cond_space(s, i - 1) && !cond_q(c_q) && !c_p)
			count++;
		check_quotes(s[i], &c_q);
		check_parentheses(s[i], &c_p);
		i++;
	}
	return (count);
}

char	**split_by_space(char *s, t_all *all, int jump_quote)
{
	t_split	all_s;

	all_s.str = s;
	all_s.c_q = (t_check_quote){0};
	all_s.c_p = 0;
	if (s == NULL)
		return (NULL);
	all_s.arr_len = count_arr_length(s);
	all_s.arr = ft_malloc((all_s.arr_len + 1) * sizeof(char *), 0, all);
	if (all_s.arr == NULL)
		return (NULL);
	all_s.arr[all_s.arr_len] = NULL;
	split_by_space2(&all_s, all, 0, jump_quote);
	return (all_s.arr);
}
