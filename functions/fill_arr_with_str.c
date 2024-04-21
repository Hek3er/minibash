/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_arr_with_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:56:28 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/21 09:14:11 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void    fill_arr_with_str(char **arr, char *str, t_all *all, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        arr[i] = str;
        i++;
    }
}