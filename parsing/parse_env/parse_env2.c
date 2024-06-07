/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:35:25 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/07 16:39:51 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

void	set_var(t_var *var, char **env, t_all *all)
{
	var->j = ft_strlen(env[var->i]);
	var->tmp_val = ft_substr(env[var->i], var->rem, var->j - var->rem, all);
}
