/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:20:58 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/18 20:35:42 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char	*s_1;
	const unsigned char	*s_2;

	if (!s1 || !s2)
		return (0);
	s_1 = (const unsigned char *)s1;
	s_2 = (const unsigned char *)s2;
	while ((*s_1 || *s_2))
	{
		if (*s_1 != *s_2)
			return (*s_1 - *s_2);
		s_1++;
		s_2++;
		i++;
	}
	return (0);
}
