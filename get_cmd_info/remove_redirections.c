/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:56:18 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/07 16:01:02 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	move_element(t_tree *b, int index)
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
	int	i;

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
