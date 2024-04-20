/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 07:04:03 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/18 22:58:25 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	is_a_dir(char *path, int *perm)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
	{
		*(perm) = 0;
		return ;
	}
	if (!(S_IEXEC & statbuf.st_mode))
	{
		*(perm) = 1;
		return ;
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		*(perm) = 2;
		return ;
	}
}
