/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_oper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:46:35 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/08 17:20:50 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static void	get_lens(char *s, t_e_oper oper_type, char c[2], int l_r_sizes[3])
{
	int				i;
	int				i_p;
	t_check_quote	c_q;

	i = 0;
	i_p = 0;
	c_q = (t_check_quote){0};
	while (s[i])
	{
		check_parentheses(s[i], &i_p);
		check_quotes(s[i], &c_q);
		if (s[i] == c[0] && s[i + 1] == c[1] && !i_p && !cond_q(c_q))
		{
			l_r_sizes[0] = i;
			if (oper_type == AND || oper_type == OR)
				l_r_sizes[1] = 2;
			else if (oper_type == PIPE)
				l_r_sizes[1] = 1;
			break ;
		}
		i++;
	}
	while (s[l_r_sizes[0] + l_r_sizes[1] + l_r_sizes[2]])
		l_r_sizes[2] += 1;
}

static void	append_str(char *str, char **arr, int size, t_all *all)
{
	char	*new_str;
	int	i;

	i = 0;
	// if (size == 0)
	// {
	// 	arr[0] = NULL;
	// 	return ;
	// }
	new_str = ft_malloc(size + 1, 0, all);
	if (!new_str)
		return ;
	while (i < size)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	arr[0] = new_str;
}

char	**split_by_oper(char *str, t_e_oper oper_type, char c[2], t_all *all)
{
	char	**arr;
	int		l_r_sizes[3];

	l_r_sizes[0] = 0;
	l_r_sizes[1] = 0;
	l_r_sizes[2] = 0;
	arr = ft_malloc(3 * sizeof (char *), 0, all);
	if (!arr)
		return (NULL);
	get_lens(str, oper_type, c, l_r_sizes);
	append_str(str, arr, l_r_sizes[0], all);
	append_str(str + l_r_sizes[0] + l_r_sizes[1], arr + 1, l_r_sizes[2], all);
	arr[2] = NULL;
	return (arr);
}
