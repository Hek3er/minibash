/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_and_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:52:22 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/11 23:34:48 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	ft_dup(int fd, t_all *all)
{
	int	x;

	x = dup(fd);
	if (x == -1)
	{
		ft_write("Dup Failed", 2, 1);
		ft_exit(NULL, all);
	}
	return (x);
}

void	ft_close(int fd, t_all *all)
{
	if (close(fd) == -1)
	{
		ft_write("Close Failed", 2, 1);
		ft_exit(NULL, all);
	}
}

void	ft_dup2(int fd1, int fd2, t_all *all)
{
	if (dup2(fd1, fd2) == -1)
	{
		ft_write("Dup2 Failed", 2, 1);
		ft_exit(NULL, all);
	}
}

void	ft_closedir(DIR *dire, t_all *all)
{
	if (closedir(dire) == -1)
	{
		ft_write("Closedir Failed", 2, 1);
		ft_exit(NULL, all);
	}
}
