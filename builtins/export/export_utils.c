/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:30:22 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/14 16:35:09 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

void	handle_export_arg(char **key_val, char **arg, int k, t_all *all)
{
	t_env	*env;

	env = all->env;
	key_val = parse_export(arg, k, all);
	if (!key_val)
		return ;
	if (parse_key(key_val, all))
		return ;
	if (!check_key(env, key_val[0]))
		append_node(&env, key_val[0], key_val[1], all);
	else
		change_val(&env, key_val, all->append, all);
}
