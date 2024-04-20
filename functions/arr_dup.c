/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:39:38 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/19 11:01:34 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	arr_dup(char **src, char **dst, int max_size)
{
	int	i;

	i = 0;
	while (src[i] && (i < max_size || max_size == 0))
	{
		dst[i] = src[i];
		i++;
	}
}