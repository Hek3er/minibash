/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:53:51 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/20 04:19:42 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static char	**append_arr_to_arr(char **arr, char **wc_marker, t_all *all)
{
	char	**arr_holder;
	char	**split_arr;
	int		i;

	i = 0;
	while (*wc_marker)
	{
		if (*wc_marker && **wc_marker == '1')
		{
			split_arr = split_by_space(arr[i], all);
			arr_holder = arr;
			arr = ft_malloc((arr_size(arr) + arr_size(split_arr) + 1) \
			* sizeof(char *), 0 , all);
			arr_dup(arr_holder, arr, i);
			arr_dup(split_arr, arr + i, arr_size(split_arr) + i);
			arr_dup(arr_holder + i + 1, arr + arr_size(split_arr) + i, 0);
			i += arr_size(split_arr);
			arr[arr_size(arr_holder) + arr_size(split_arr)] = NULL;
		}
		else
			i++;
		wc_marker++;
	}
	arr[i] = NULL;
	return (arr);
}

void	append_filename(char *filename, char **new_str, t_all *all)
{
	char	*tmp;

	tmp = *new_str;
	if (!*new_str)
		*new_str = ft_strdup(filename, all);
	else
		*new_str = ft_strjoin(*new_str, filename, all);
	tmp = *new_str;
	*new_str = ft_strjoin(*new_str, " ", all);
}

int	wildcard_exist(char *str)
{
	while (*str)
	{
		if (*str == '*')
			return (1);
		str++;
	}
	return (0);
}
void	find_wildcard(char **arr, t_str_list *files, char **wc_marker, \
t_all *all)
{
	t_str_list	*tmp_files;
	char		*new_str;

	tmp_files = files;
	new_str = NULL;
	while (*arr)
	{
		if (!wildcard_exist(*arr) && arr++ && wc_marker++)
			continue ;
		while (files)
		{
			if (check_wildcard(files->str, *arr))
				append_filename(files->str, &new_str, all);
			files = files->next;
		}
		if (new_str)
		{
			*arr = new_str;
			*wc_marker = "1";
		}
		new_str = NULL;
		files = tmp_files;
		arr++;
		wc_marker++;
	}
}

char	**get_wildcard(char **arr, t_all *all)
{
	t_str_list	*all_files;
	char		**wc_marker;

	all_files = NULL;
	wc_marker = ft_malloc((arr_size(arr) + 1) * sizeof(char *), 0, all);
	if (!wc_marker)
		return (NULL);
	wc_marker[arr_size(arr)] = NULL;
	fill_arr_with_str(wc_marker, "0", all);
	get_files(&all_files, ".", all);
	find_wildcard(arr, all_files, wc_marker, all);
	return (append_arr_to_arr(arr, wc_marker, all));
}
