/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_docs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:33:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/08 17:01:01 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	remove_docs(t_all *all)
{
	t_str_list	*docs;
	char		*path;
	char		*pid;

	get_files(&docs, H_DOC_PATH, all);
	while (docs)
	{
		pid = unsigned_to_str(getpid(), all);
		path = ft_strjoin(H_DOC_PATH, pid, all);
		if (!ft_strncmp(docs->str, pid, ft_strlen(pid)))
		{
			path = ft_strjoin(H_DOC_PATH, docs->str, all);
			unlink(path);
		}
		docs = docs->next;
	}
}
