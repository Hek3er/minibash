/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 08:15:38 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/28 18:17:14 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minibash.h"

static int	count_str_without_quotes(char *str)
{
	t_check_quote	c_q;
	int				i;
	int				size;

	c_q = (t_check_quote){0};
	size = 0;
	i = 0;
	while (str[i])
	{
		check_quotes(str[i], &c_q);
		if (cond_q(c_q) && ((str[i] == '"' && c_q.is_dq) || \
		(str[i] == '\'' && c_q.is_sq)))
			i++;
		if (!cond_q(c_q) && str[i] != '"' && str[i] != '\'')
			size++;
		if (cond_q(c_q) && !((str[i] == '"' && c_q.is_dq) || \
		(str[i] == '\'' && c_q.is_sq)))
			size++;
		i++;
	}
	return (size);
}

static void	clone_to_new_str(char *src, char *dst, t_check_quote c_q)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (src[i])
	{
		check_quotes(src[i], &c_q);
		if (cond_q(c_q) && ((src[i] == '"' && c_q.is_dq) || \
		(src[i] == '\'' && c_q.is_sq)))
			i++;
		if (!cond_q(c_q) && src[i] != '"' && src[i] != '\'')
		{
			dst[j] = src[i];
			j++;
		}
		if (cond_q(c_q) && !((src[i] == '"' && c_q.is_dq) || \
		(src[i] == '\'' && c_q.is_sq)))
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
}

static void	remove_quotes(char **str, t_all *all)
{
	int				str_len;
	char			*new_str;

	while (*str)
	{
		str_len = count_str_without_quotes(*str);
		new_str = ft_malloc(str_len + 1, 0, all);
		if (!new_str)
			return ;
		clone_to_new_str(*str, new_str, (t_check_quote){0});
		*str = new_str;
		str ++;
	}
}

int	get_cmd_info(t_tree *branch, t_all *all)
{
	char	**pre_env_arr;
	char	*str;

	all->error = NULL;
	str = branch->cmd_str;
	pre_env_arr = split_by_space(str, all, 1);
	get_environment(all, &str);
	branch->cmd = split_by_space(str, all, 1);
	branch->input = get_input_output(branch->cmd, 0, pre_env_arr, all);
	branch->output = get_input_output(branch->cmd, 1, pre_env_arr, all);
	remove_quotes(branch->cmd, all);
	branch->cmd = get_wildcard(branch->cmd, all);
	if (branch->here_doc == 0)
		branch->here_doc = \
		get_here_doc(str, &branch->input, branch->doc_i, all);
	all->envp = linked_list_to_arr(all);
	if (all->error)
		return (1);
	return (0);
}
