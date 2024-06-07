/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 08:15:38 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/07 13:44:59 by ealislam         ###   ########.fr       */
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

void	remove_quotes(char **str, t_all *all)
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

static void	move_element(t_tree *b, int index)
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
		if (!(ft_strlen(b->cmd[i]) > 2) && \
		(cond_oper(b->cmd[i], INPUT) || cond_oper(b->cmd[i], OUTPUT) || \
		cond_oper(b->cmd[i], H_DOC) || cond_oper(b->cmd[i], APPEND)))
		{
			move_element(b, i);
			move_element(b, i);
		}
		else
			i++;
	}
}

void	seperate_env(t_tree *branch, t_all *all, int index, int *b_index)
{
	char	**arr;
	char	**env_seperated;
	int		env_size;
	int		i;

	i = 0;
	env_seperated = split_by_space(*(branch->cmd + index), all, 0);
	env_size = arr_size(env_seperated);
	if (!env_size)
		(*b_index)++;
	else
		(*b_index) += env_size;
	if (env_seperated && env_seperated[0] && !env_seperated[1])
		return ;
	arr = ft_malloc((arr_size(branch->cmd) + env_size) * sizeof(char *), 0, all);
	if (!arr)
		return ;
	while (i < index)
	{
		arr[i] = branch->cmd[i];
		i ++;
	}
	while (*env_seperated)
	{
		arr[i] = *env_seperated;
		i++;
		env_seperated++;
	}
	while (i < arr_size(branch->cmd) + env_size - 1)
	{
		arr[i] = branch->cmd[i - env_size + 1];
		i++;
	}
	arr[i] = NULL;
	branch->cmd = arr;
	int y = 0;
}

void	get_cmd_array_quotes(t_tree *branch, t_all *all, char **str, int quote)
{
	int	i;

	i = 0;
	*str = ft_strdup(branch->cmd_str, all);
	all->add_quotes_to_env = quote;
	branch->cmd = split_by_space(*str, all, 1);
	while (branch->cmd && branch->cmd[i])
	{
		get_environment(all, branch->cmd + i);
		if (branch->cmd[i] && branch->cmd[i][0])
			seperate_env(branch, all, i, &i);
		else
			i++;
	}
}

void	remove_empty_element(t_tree *branch, t_all *all)
{
	int	i;

	i = 0;
	while (branch->cmd && branch->cmd[i])
	{
		if (!branch->cmd[i][0])
			move_element(branch, i);
		else
			i++;
	}
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
	//----------------------------------
	int i = 0;
	// while (branch->cmd[i])
	// {
	// 	printf("=======%s\n", branch->cmd[i]);
	// 	i++;
	// }
	//----------------------------------
	remove_redirectionals(branch);
	remove_quotes(branch->cmd, all);

	branch->cmd = get_wildcard(branch->cmd, all);
	if (branch->here_doc == 0)
		branch->here_doc = \
		get_here_doc(str, &branch->input, branch->doc_i, all);
	all->envp = linked_list_to_arr(all);
	remove_empty_element(branch, all);
	if (all->error)
		return (1);
	// printf("ffffff %d %d\n",branch->input, branch->output );
	return (0);
	// printf("%s")
}
