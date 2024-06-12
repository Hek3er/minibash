/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:19:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/12 12:34:56 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static char	*move_until_paranthes_close(char *str)
{
	int				i;
	int				c_p;

	i = 0;
	c_p = 0;
	if (str && str[i])
		check_parentheses(str[i], &c_p);
	while (str && str[i] && c_p)
	{
		check_parentheses(str[i], &c_p);
		i++;
	}
	return (str + i);
}

static int	check_if_doc_is_last(char *str, t_all *all)
{
	int		i;
	int		is_last;
	char	**arr;

	is_last = 0;
	i = 0;
	str = move_until_paranthes_close(str);
	arr = split_by_space(str, all, 0);
	while (arr && arr[i])
	{
		if (cond_oper(arr[i], H_DOC))
			is_last = 1;
		if (cond_oper(arr[i], INPUT))
			is_last = 0;
		i++;
	}
	return (is_last);
}

int	get_here_doc(char *str, int *input_fd, int here_doc_i, t_all *all)
{
	char	*str1;
	char	*str2;
	char	*doc_name;
	int		doc_fd;

	if (!check_if_doc_is_last(str, all))
		return (0);
	str1 = ttyname(STDIN_FILENO) + 5;
	str2 = unsigned_to_str(here_doc_i, all);
	doc_name = ft_strjoin(str1, str2, all);
	doc_name = ft_strjoin(H_DOC_PATH, doc_name, all);
	if (access(doc_name, F_OK) == -1)
		return (0);
	doc_fd = ft_open(doc_name, OPEN_READ, all, 0);
	if (doc_fd < 0)
		return (-1);
	*input_fd = 0;
	return (doc_fd);
}
