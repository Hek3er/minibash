/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:19:59 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/19 00:44:07 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

void	ft_exit(t_all *all)
{
	// remove_docs(all);
	// ft_open(NULL, 0, NULL, 1);
	// ft_malloc(0, 1, NULL);
	ft_write("exit", 0, 1);
	// printf("exit\n");
	exit(0);
}
