/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_stat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 01:37:03 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/25 10:51:40 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	exit_stat(int code, int flag)
{
	static int	exit_code = 0;

	if (flag == 1)
		exit_code = code;
	return (exit_code);
}
