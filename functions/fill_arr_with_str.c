/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_arr_with_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:56:28 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/23 04:01:31 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void    fill_arr_with_str(char **arr, char *str, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        arr[i] = str;
        i++;
    }
}