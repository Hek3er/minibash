/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:58:41 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/16 02:26:30 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

char	*ft_strjoin(char const *s1, char const *s2, t_all *all)
{
	char	*str;
	char	*result;		

	if (s1 == NULL)
		return (NULL);
	if (!s2)
		return ((char *)s1);
	str = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, 0, all);
	if (str == NULL)
		exit(12);
	result = str;
	while (*s1)
	{
		*str = *s1;
		str++;
		s1++;
	}
	while (*s2)
	{
		*str = *s2;
		str++;
		s2++;
	}
	*str = '\0';
	return (result);
}
