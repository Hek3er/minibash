/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:55:32 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/08 15:57:45 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	fill_command(char **arr, t_tree *branch, \
int index, char **env_seperated)
{
	int	i;
	int	env_size;

	env_size = arr_size(env_seperated);
	i = 0;
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
}

void	seperate_env(t_tree *branch, t_all *all, int index, int *b_index)
{
	char	**arr;
	char	**env_seperated;
	int		env_size;

	env_seperated = split_by_space(*(branch->cmd + index), all, 1);
	env_size = arr_size(env_seperated);
	if (!env_size)
		(*b_index)++;
	else
		(*b_index) += env_size;
	arr = ft_malloc((arr_size(branch->cmd) + env_size) * sizeof(char *), \
	0, all);
	if (!arr)
		return ;
	fill_command(arr, branch, index, env_seperated);
	branch->cmd = arr;
}
