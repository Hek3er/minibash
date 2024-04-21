/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:05:54 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/21 06:45:09 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	delimiter_size(char *s, t_all *all)
{
	char			*delim;
	t_check_quote	cq;
	int				i;
	int				count;

	i = 0;
	count = 0;
	cq = (t_check_quote){0};
	while (s[i] == ' ')
		i++;
	if (!s[i] || s[i] == '(' || s[i] == ')' || cond_oper(s + i, NONE))
		(all->error = "minibash: syntax error", exit_stat(258, 1));
	while (s[i])
	{
		check_quotes(s[i], &cq);
		if (((!cq.is_dq && s[i] == '\'') || (!cq.is_sq && s[i] == '"')) && i++)
			continue;
		if (!cond_q(cq) && (s[i] == '(' || s[i] == ')' || \
		cond_oper(s + i, NONE) || s[i] == ' '))
			break ;
		i++;
		count++;
	}
	return (count);
}

static char	*get_delimiter(char *s, t_all *all)
{
	char			*delim;
	t_check_quote	cq;
	int				i;

	delim = ft_malloc(delimiter_size(s, all) + 2, 0, all);
	if (!delim)
		return (NULL);
	i = 0;
	cq = (t_check_quote){0};
	while (*s == ' ')
		s++;
	while (s[i])
	{
		check_quotes(s[i], &cq);
		if (((!cq.is_dq && s[i] == '\'') || (!cq.is_sq && s[i] == '"')) && s++)
			continue;
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

static void	fill_doc(int doc_fd, char *delimiter, t_all *all)
{
	char	*str;
	int		i;
	char	*remain;

	if (!delimiter)
		return ;
	signal(SIGINT, &handle_signal_doc);
	while (1)
	{
		str = readline(">");
		if (!str)
			break ;
		if (!ft_strncmp(str, delimiter, ft_strlen(delimiter) - 1))
		{
			free(str);
			break ;
		}
		ft_write(str, doc_fd, 0);
		ft_write("\n", doc_fd, 0);
		free(str);
	}
	signal(SIGINT, &handle_signal);
}

static void	create_doc(unsigned int here_doc_i, char *str, \
t_all *all)
{
	char	*pid;
	char	*doc_i;
	char	*doc_name;
	int		doc_fd;

	pid = unsigned_to_str(getpid(), all);
	doc_i = unsigned_to_str(here_doc_i, all);
	doc_name = ft_strjoin(pid, doc_i, all);
	doc_name = ft_strjoin(H_DOC_PATH, doc_name, all);
	doc_fd = ft_open(doc_name, OPEN_TRUNC, all, 0);
	if (doc_fd < 0)
		return ;
	fill_doc(doc_fd, get_delimiter(str, all), all);
	ft_open(NULL, 0, NULL, doc_fd);
}

void	check_here_doc(char *str, t_all *all)
{
	t_check_hdoc	hd;

	hd = (t_check_hdoc){0};
	while (*str)
	{
		(check_quotes(*str, &hd.c_q), check_parentheses(*str, &hd.i_p));
		if (!hd.i_p && hd.p_tracker)
			hd.here_doc_i++;
		hd.p_tracker = hd.i_p;
		if (*str == ')' && !cond_q(hd.c_q))
			hd.here_doc_i--;
		if (cond_oper(str, AND) || cond_oper(str, OR) || cond_oper(str, PIPE)\
		 || *str == '(' && !cond_q(hd.c_q))
			hd.here_doc_i++;
		if (!cond_q(hd.c_q) && cond_oper(str, H_DOC))
			create_doc(hd.here_doc_i, str + 2, all);
		if (all->error)
			return ;
		str++;
	}
	if (cond_q(hd.c_q))
	{
		all->error = "minibash: syntax error";
		exit_stat(258, 1);
	}
}
