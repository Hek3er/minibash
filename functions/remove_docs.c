/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_docs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:33:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/12 12:34:53 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	remove_docs(t_all *all)
{
	t_str_list	*docs;
	char		*path;
	char		*ttynm;

	get_files(&docs, H_DOC_PATH, all);
	while (docs)
	{
		// pid = unsigned_to_str(getpid(), all);
		ttynm = ttyname(STDIN_FILENO) + 5;
		path = ft_strjoin(H_DOC_PATH, ttynm, all);
		if (!ft_strncmp(docs->str, ttynm, ft_strlen(ttynm)))
		{
			path = ft_strjoin(H_DOC_PATH, docs->str, all);
			if (unlink(path) == -1)
			{
				ft_write("unlink failed", 2, 1);
				ft_exit(NULL, all);
			}
		}
		docs = docs->next;
	}
}
