/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:45:42 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/23 05:31:33 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static int	get_prev_dir(t_all *all)
{
	char	*env_path;
	int		i;
	int		flag;

	flag = 0;
	env_path = get_value(all->env, "PWD");
	i = ft_strlen(env_path);
	if (handle_parrent_directory(env_path, i, flag, all))
		return (0);
	change_val(&all->env, (char *[]){"PWD", getcwd(NULL, 0)}, 0, all);
	change_val(&all->env, (char *[]){"OLDPWD", env_path}, 0, all);
	return (1);
}

int	cd(char **arg, t_all *all)
{
	int		i;
	char	*cwd;

	i = 1;
	cwd = getcwd(NULL, 0);
	if (!arg[i])
	{
		if (no_arg_cd(cwd, all))
			return (0);
	}
	else
	{
		if (arg[1][0] == '.' && arg[1][1] == '.' && !cwd)
			return (get_prev_dir(all), 0);
		if (handle_arg_cd(arg, cwd, all))
			return (0);
	}
	exit_stat(0, 1);
	return (1);
}
