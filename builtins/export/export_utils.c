/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:30:22 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/07 16:12:02 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

void	handle_export_arg(char **key_val, char **arg, int k, t_all *all)
{
	t_env	*env;
	char	*tmp;

	env = all->env;
	key_val = parse_export(arg, k, all);
	if (!key_val)
		return ;
	if (parse_key(key_val, all))
		return ;
	if (key_val[1] && key_val[1][0] == '$')
	{
		tmp = ft_strdup(key_val[1], all);
		if (!tmp)
			return ;
		key_val[1] = ft_strjoin("\\", tmp, all);
		if (!key_val[1])
			return ;
	}
	if (!check_key(env, key_val[0]))
		append_node(&env, key_val[0], key_val[1], all);
	else
		change_val(&env, key_val, all->append, all);
}
