/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:44 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/25 10:55:52 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static int	size_of_unsigned(unsigned int num)
{
	int	i;

	i = 0;
	while (num >= 10)
	{
		num = num / 10;
		i++;
	}
	i++;
	return (i);
}

static void	unsigned_to_str2(unsigned int num, char *str)
{
	char	c;

	c = '0' + (num % 10);
	if (num < 10)
	{
		*str = c;
		return ;
	}
	unsigned_to_str2(num / 10, str - 1);
	*str = c;
}

char	*unsigned_to_str(unsigned int num, t_all *all)
{
	char	*str;
	int		size;

	size = size_of_unsigned(num);
	str = ft_malloc (size + 1, 0, all);
	if (!str)
		return (NULL);
	str[size] = '\0';
	unsigned_to_str2(num, str + size - 1);
	return (str);
}
