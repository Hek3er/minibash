/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hdoc_delimiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:45:15 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/05 17:02:12 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"


static int	delimiter_size(char *s, t_all *all, t_check_quote cq)
{
	int				i;
	int				count;

	i = 0;
	count = 0;
	while (is_white_space(s[i]))
		i++;
	if (!s[i] || s[i] == '(' || s[i] == ')' || cond_oper(s + i, NONE))
	{
		all->error = "minibash: syntax error";
		exit_stat(258, 1);
	}
	while (s[i])
	{
		check_quotes(s[i], &cq);
		if (((!cq.is_dq && s[i] == '\'') || (!cq.is_sq && s[i] == '"')) && i++)
			continue ;
		if (!cond_q(cq) && (s[i] == '(' || s[i] == ')' || \
		cond_oper(s + i, NONE) || s[i] == ' '))
			break ;
		i++;
		count++;
	}
	return (count);
}

char	*get_delimiter(char *s, t_all *all, t_check_quote cq)
{
	char			*delim;
	int				i;

	delim = ft_malloc(delimiter_size(s, all, (t_check_quote){0}) + 2, 0, all);
	if (!delim)
		return (NULL);
	i = 0;
	while (is_white_space(*s))
		s++;
	while (s[i])
	{
		check_quotes(s[i], &cq);
		if (cond_q(cq))
			all->quote_in_hdoc_delimiter = 1;
		if (((!cq.is_dq && s[i] == '\'') || (!cq.is_sq && s[i] == '"')) && s++)
			continue ;
		if (!cond_q(cq) && (s[i] == '(' || s[i] == ')' || \
		cond_oper(s + i, NONE) || s[i] == ' '))
			break ;
		delim[i] = s[i];
		i++;
	}
	delim[i] = '\n';
	delim[i + 1] = '\0';
	return (delim);
}
