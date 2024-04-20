/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:33:03 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/03 12:54:35 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

t_size	get_s(char *str)
{
	t_size	sizes;

	sizes.s_to_nl = 0;
	sizes.s_to_null = 0;
	while (str && str[sizes.s_to_null])
		sizes.s_to_null++;
	while (str && str[sizes.s_to_nl] && str[sizes.s_to_nl] != '\n')
		sizes.s_to_nl++;
	if (str && str[sizes.s_to_nl] == '\n')
		sizes.s_to_nl++;
	return (sizes);
}

void	str_join(char *src, char **dst, char *new_dst)
{
	char	*new_dst_head;
	char	*dst_tmp;

	dst_tmp = *dst;
	new_dst_head = new_dst;
	while (dst_tmp && *dst_tmp)
		*new_dst++ = *dst_tmp++;
	while (*src && *src != '\n')
		*new_dst++ = *src++;
	if (*src == '\n')
		*new_dst++ = '\n';
	*new_dst = '\0';
	*dst = new_dst_head;
}

int	check_n(char *bfr)
{
	while (*bfr)
	{
		if (*bfr == '\n')
			return (1);
		bfr++;
	}
	return (0);
}

char	*free_and_return_null(char **remain, char **final, char **cur_buf)
{
	return (NULL);
}
