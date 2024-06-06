/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:08:42 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/06 14:42:09 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

int	cond_q(t_check_quote c_q)
{
	if (c_q.is_dq || c_q.is_sq)
		return (1);
	return (0);
}

int	cond_space(char *str, int i)
{
	if (str[i] == ' ')
		return (1);
	return (0);
}

int	cond_jump_quote(char c, t_check_quote c_q, int jump_quote)
{
	if (jump_quote)
		return (0);
	if (c == '\'' && !c_q.is_dq)
		return (1);
	if (c == '\"' && !c_q.is_sq)
		return (1);
	return (0);
}

int	cond_oper(char *str, t_e_oper oper)
{
	if (!str)
		return (NONE);
	if ((*str == '<' && *(str + 1) == '<') && (oper == H_DOC || oper == NONE))
		return (H_DOC);
	if ((*str == '<' && *(str + 1) != '<') && (oper == INPUT || oper == NONE))
		return (INPUT);
	if ((*str == '>' && *(str + 1) == '>') && (oper == APPEND || oper == NONE))
		return (APPEND);
	if ((*str == '>' && *(str + 1) != '>') && (oper == OUTPUT || oper == NONE))
		return (OUTPUT);
	if ((*str == '|' && *(str + 1) == '|') && (oper == OR || oper == NONE))
		return (OR);
	if ((*str == '|' && *(str + 1) != '|') && (oper == PIPE || oper == NONE))
		return (PIPE);
	if ((*str == '&' && *(str + 1) == '&') && (oper == AND || oper == NONE))
		return (AND);
	return (NONE);
}

int	cond_redirect(char *str)
{
	if (!str)
		return (0);
	if (*str == '>' && *(str + 1) == '>')
		return (2);
	if (*str == '<' && *(str + 1) == '<')
		return (2);
	if (*str == '<' && *(str + 1) != '<')
		return (1);
	if (*str == '>' && *(str + 1) != '>')
		return (1);
	return (0);
}
