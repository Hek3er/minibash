/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:45:42 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/21 23:07:30 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

int	cd(char **arg, t_all *all)
{
	int		i;
	char	*path;
	char	*cwd;

	i = 1;
	cwd = getcwd(NULL, 0);
	if (!arg[i])
	{
		if (!check_key(all->env, "HOME"))
		{
			(all->error = "minibash: cd: HOME not set", exit_stat(1, 1));
			return (0);
		}
		else
		{
			path = get_value(all->env, "HOME");
			if (path && !path[0])
				return (exit_stat(0, 1), 0);
			if (!path)
			{
				(all->error = "minibash: cd: HOME not set", exit_stat(1, 1));
				return (0);
			}
			if (chdir(path) == -1)
			{
				(all->error = strerror(errno), exit_stat(1, 1));
				return (0);
			}
			change_val(&all->env, (char *[]){"PWD", getcwd(NULL, 0)}, 0, all);
			change_val(&all->env, (char *[]){"OLDPWD", cwd}, 0, all);
		}
	}
	else
	{
		if (arg[1][0] == '-')
			arg[1] = get_value(all->env, "OLDPWD");
		if (arg[1][ft_strlen(arg[1]) - 1] == '\\' && arg[2])
		{
			arg[1] = ft_strjoin(ft_substr(arg[1], 0, ft_strlen(arg[1]) - 1, all), " ", all);
			arg[1] = ft_strjoin(arg[1], arg[2], all);
		}
		if (chdir(arg[1]) == -1)
		{
			all->tmp = ft_strjoin("minibash: cd: ", arg[1], all);
			(all->tmp = ft_strjoin(all->tmp, ": ", all));
			(all->error = ft_strjoin(all->tmp, strerror(errno), all), exit_stat(1, 1));
			return (0);
		}
		change_val(&all->env, (char *[]){"PWD", getcwd(NULL, 0)}, 0, all);
		change_val(&all->env, (char *[]){"OLDPWD", cwd}, 0, all);
	}
	exit_stat(0, 1);
	return (1);
}
