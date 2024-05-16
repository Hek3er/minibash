/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:42:43 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/25 10:55:33 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	ft_write(char *str, int fd, int new_line)
{
	while (*str)
	{
		write (fd, str, 1);
		str++;
	}
	if (new_line == 1)
		write(fd, "\n", 1);
}
