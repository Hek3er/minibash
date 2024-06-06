/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:05:54 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/06 12:33:57 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static void	fill_doc(int doc_fd, char *delimiter, t_all *all)
{
	char	*str;

	if (!delimiter)
		return ;
	if (all->quote_in_hdoc_delimiter)
		all->env_for_hdoc = 0;
	signal(SIGINT, &handle_signal_doc);
	while (1)
	{
		str = readline("> ");
		if (!str || set_delim(0, 0))
		{
			free(str);
			break ;
		}
		if (ft_strlen(str) == ft_strlen(delimiter) - 1 && \
		!ft_strncmp(str, delimiter, ft_strlen(delimiter) - 1))
		{
			free(str);
			break ;
		}
		if (!all->quote_in_hdoc_delimiter)
			get_environment(all, &str);
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
	fill_doc(doc_fd, get_delimiter(str, all, (t_check_quote){0}), all);
	ft_open(NULL, 0, NULL, doc_fd);
}

void	check_here_doc(char *str, t_all *all)
{
	t_check_hdoc	hd;

	hd = (t_check_hdoc){0};
	all->quote_in_hdoc_delimiter = 0;
	all->env_for_hdoc = 1;
	while (*str)
	{
		check_quotes(*str, &hd.c_q);
		check_parentheses(*str, &hd.i_p);
		if (cond_oper(str, AND) || cond_oper(str, OR) || cond_oper(str, PIPE))
			hd.here_doc_i++;
		if (!cond_q(hd.c_q) && cond_oper(str, H_DOC))
			create_doc(hd.here_doc_i, str + 2, all);
		if (all->error)
			return ;
		str++;
	}
	all->env_for_hdoc = 0;
	if (cond_q(hd.c_q))
	{
		all->error = "minibash: syntax error";
		exit_stat(258, 1);
	}
}
