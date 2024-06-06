/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 08:15:38 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/06 14:39:29 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minibash.h"

static int	str_length_without_quotes(char *str)
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
		{
			i++;
			continue ;
		}
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
		{
			i++;
			continue ;
		}
		if ((!cond_q(c_q) && src[i] != '"' && src[i] != '\'') || \
		(cond_q(c_q) && !((src[i] == '"' && c_q.is_dq) || \
		(src[i] == '\'' && c_q.is_sq))))
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

	while (str && *str)
	{
		str_len = str_length_without_quotes(*str);
		new_str = ft_malloc(str_len + 1, 0, all);
		if (!new_str)
			return ;
		clone_to_new_str(*str, new_str, (t_check_quote){0});
		*str = new_str;
		str ++;
	}
}

static void	move_redirectionals(t_tree *b, int index)
{
	int	j;

	j = index;
	while (b->cmd[j])
	{
		if (!b->cmd[j + 1])
			b->cmd[j] = NULL;
		b->cmd[j] = b->cmd[j + 1];
		j++;
	}
}	

void	remove_redirectionals(t_tree *b)
{
	int				i;

	t_check_quote	c_q;
	i = 0;
	while (b->cmd && b->cmd[i])
	{
		printf("%s ***\n",b->cmd[i]);
		if (!(ft_strlen(b->cmd[i]) > 2) && \
		(cond_oper(b->cmd[i], INPUT) || cond_oper(b->cmd[i], OUTPUT) || \
		cond_oper(b->cmd[i], H_DOC) || cond_oper(b->cmd[i], APPEND)))
		{
			printf("xxx\n");
			move_redirectionals(b, i);
			move_redirectionals(b, i);
		}
		else
			i++;
	}
}

void	get_cmd_array_quotes(t_tree *branch, t_all *all, char **str, int quote)
{
	*str = ft_strdup(branch->cmd_str, all);
	all->add_quotes_to_env = quote;
	get_environment(all, str);
	branch->cmd = split_by_space(*str, all, 1);
}

int	get_cmd_info(t_tree *branch, t_all *all)
{
	char	**pre_env_arr;
	char	*str;

	all->error = NULL;
	pre_env_arr = split_by_space(branch->cmd_str, all, 1);
	//-------may cause problems--------
	get_cmd_array_quotes(branch, all, &str, 1);
	get_input_output(branch->cmd, branch, pre_env_arr, all);
	remove_quotes(branch->cmd, all);
	//----------------------------------
	get_cmd_array_quotes(branch, all, &str, 0);
	remove_redirectionals(branch);
	remove_quotes(branch->cmd, all);
	//----------------------------------
	branch->cmd = get_wildcard(branch->cmd, all);
	if (branch->here_doc == 0)
		branch->here_doc = \
		get_here_doc(str, &branch->input, branch->doc_i, all);
	all->envp = linked_list_to_arr(all);
	if (all->error)
		return (1);
	return (0);
}
