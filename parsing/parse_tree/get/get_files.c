/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 09:23:27 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/08 17:15:51 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

void sort_list(t_str_list *head) {
    int			swapped;
    t_str_list	*ptr;
    t_str_list	*last;
	char		*tmp_str;

	last = NULL;
	swapped = 1;
	while (swapped)
	{
        swapped = 0;
        ptr = head;

        while (ptr->next != last) 
		{
            if (ft_strcmp(ptr->str, ptr->next->str) > 0) {
                tmp_str = ptr->str;
                ptr->str = ptr->next->str;
                ptr->next->str = tmp_str;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }
}

static t_str_list	*append_file(char *str, t_str_list *all_files, t_all *all)
{
	t_str_list	*file;

	file = ft_malloc(sizeof(t_str_list), 0, all);
	if (!file)
		return (NULL);
	file->str = ft_strdup(str, all);
	file->next = NULL;
	if (!all_files)
		all_files = file;
	else
		all_files->next = file;
	return (file);
}

void	get_files(t_str_list **all_files, char *path, t_all *all)
{
	t_str_list		*tmp;
	t_str_list		*head;
	DIR				*dir;
	struct dirent	*entry;

	head = NULL;
	tmp = NULL;
	dir = opendir(path);
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		tmp = append_file(entry->d_name, tmp, all);
		if (!head)
			head = tmp;
		entry = readdir(dir);
	}
	closedir(dir);
	*all_files = head;
	if (*all_files)
		sort_list(*all_files);
}
