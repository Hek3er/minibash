/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:56:18 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/08 18:10:57 by azainabi         ###   ########.fr       */
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

static int	cmp_quote(char *str, char *cmd, t_all *all)
{
	char	*cmd_without_quote[2];

	cmd_without_quote[0] = cmd;
	cmd_without_quote[1] = NULL;
	remove_quotes(cmd_without_quote, all);
	return (ft_strcmp(cmd_without_quote[0], str));
}

static int	is_redir(char *s)
{
	if (cond_oper(s, INPUT) || cond_oper(s, OUTPUT) || \
		cond_oper(s, H_DOC) || cond_oper(s, APPEND))
		return (1);
	return (0);
}

void	remove_redirectionals(t_tree *b, char **arr, t_all *all)
{
	int	i;
	int	moved;

	i = 0;
	moved = 0;
	while (b->cmd && b->cmd[i] && arr[i])
	{
		if (!(ft_strlen(b->cmd[i]) > 2) && arr[i] && \
		(is_redir(b->cmd[i]) && !cmp_quote(b->cmd[i], arr[i], all)))
		{
			move_element(b, i);
			move_element(b, i);
			arr += 2;
			moved = 1;
		}
		else if (ft_strcmp(b->cmd[i], arr[i]) && moved)
			move_element(b, i);
		else
		{
			i++;
			moved = 0;
		}
	}
}
