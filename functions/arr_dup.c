/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:39:38 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/25 10:50:22 by azainabi         ###   ########.fr       */
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
