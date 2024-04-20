/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_to_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:08:57 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/05 15:17:58 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

char	**linked_list_to_arr(t_all *all)
{
	t_env	*tmp;
	int		i;
	char	**arr;

	tmp = all->env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	tmp = all->env;
	arr = ft_malloc((sizeof(char *) * i + 1), 0, all);
	if (!arr)	
		return (NULL);
	i = 0;
	while (tmp)
	{
		arr[i] = ft_strjoin(tmp->key, "=", all);
		arr[i] = ft_strjoin(arr[i], tmp->value, all);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}