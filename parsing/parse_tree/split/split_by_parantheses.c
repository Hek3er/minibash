/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_parantheses.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:57:04 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/23 04:06:21 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

// static int	get_fds(char *s, int *input, int *output, t_all *all)
// {
// 	char	**arr;
// 	int		i;

// 	i = 0;
// 	arr = split_by_space(s, all);
// 	while (arr && arr[i])
// 	{
// 		if (!arr[i + 1] || (cond_redirect(arr[i]) && \
// 		cond_redirect(arr[i + 1])))
// 			return (all->error = "minibash:d syntax error", exit_stat(258, 1), 0);
// 		i += 2;
// 	}
// 	*input = get_input_output(arr, 0, arr, all);
// 	*output = get_input_output(arr, 1, arr, all);
// 	if (all->error)
// 		return (all->error = NULL, *input = -1, 0);
// 	return (0);
// }

// static void	check_end_and_get_fds(char *s, int *input, int *output, t_all *all)
// {
// 	int				oper_size;
// 	t_check_quote	cq;
// 	char			*file_name;

// 	if (cond_oper(s, PIPE) || cond_oper(s, AND) || cond_oper(s, OR))
// 	{
// 		(*input = 0, *output = 1);
// 		return ;
// 	}
// 	oper_size = cond_redirect(s);
// 	if (!s || !oper_size)
// 	{
// 		all->error = "minibash: syntax error";
// 		exit_stat(258, 1);
// 		return ;
// 	}
// 	if (!cond_redirect(s))
// 	{
// 		*input = 0;
// 		*output = 1;
// 	}
// 	get_fds(s, input, output, all);
// }

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

static int	get_para_size(char *str, t_all *all)
{
	int				i;
	int				size;
	int				p_i;
	t_check_quote	c_q;

	i = 0;
	size = 0;
	p_i = 0;
	c_q = (t_check_quote){0};
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
		(all->error = "minibash: syntax error", exit_stat(258, 1));
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
	new_str = ft_malloc(get_para_size(str, all) + 1, 0, all);
	if (!new_str)
		return (NULL);
	while (is_white_space(str[i]))
		i++;
	i++;
	while (j < get_para_size(str, all))
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);
}
