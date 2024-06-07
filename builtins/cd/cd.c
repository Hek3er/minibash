/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:45:42 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/07 16:06:43 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static int	get_prev_dir(t_all *all)
{
	char	*env_path;
	char	*current_dir;
	int		i;
	int		flag;

	flag = 0;
	current_dir = ft_malloc(PATH_MAX, 0, all);
	if (!current_dir)
		return (0);
	env_path = get_value(all->env, "PWD", all);
	if (!env_path)
		return (0);
	i = ft_strlen(env_path);
	if (handle_parrent_directory(env_path, i, flag, all))
		return (0);
	getcwd(current_dir, PATH_MAX);
	change_val(&all->env, (char *[]){"PWD", current_dir}, 0, all);
	change_val(&all->env, (char *[]){"OLDPWD", env_path}, 0, all);
	return (1);
}

int	calculate_backslash(char *cwd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cwd[i])
	{
		if (cwd[i] == '/')
			count++;
		i++;
	}
	return (count);
}

int	cd(char **arg, t_all *all)
{
	int		i;
	char	*cwd;

	i = 1;
	cwd = ft_malloc(PATH_MAX, 0, all);
	if (!cwd)
		return (0);
	getcwd(cwd, PATH_MAX);
	if (!arg[i])
	{
		if (no_arg_cd(cwd, all))
			return (0);
	}
	else
	{
		if (arg[1][0] == '.' && arg[1][1] == '.' && ft_strlen(arg[1]) <= 2 \
		&& calculate_backslash(cwd) > 1 && arg[1][ft_strlen(arg[1]) - 1] == '.')
			return (get_prev_dir(all), 0);
		if (handle_arg_cd(arg, cwd, all))
			return (0);
	}
	exit_stat(0, 1);
	return (1);
}
