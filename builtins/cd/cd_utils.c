/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 04:43:55 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/24 08:26:36 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

int	no_arg_cd(char *cwd, t_all *all)
{
	char	*path;
	char	*new_wd;

	new_wd = ft_malloc(PATH_MAX, 0, all);
	if (!new_wd)
		return (1);
	if (!check_key(all->env, "HOME"))
		return (all->error = "minibash: cd: HOME not set", \
		exit_stat(1, 1), 1);
	else
	{
		path = get_value(all->env, "HOME");
		if (path && !path[0])
			return (exit_stat(0, 1), 1);
		if (!path)
			return (all->error = "minibash: cd: HOME not set", \
			exit_stat(1, 1), 1);
		if (chdir(path) == -1)
			return (all->error = strerror(errno), \
			exit_stat(1, 1), 1);
		getcwd(new_wd, PATH_MAX);
		change_val(&all->env, (char *[]){"PWD", new_wd}, 0, all);
		change_val(&all->env, (char *[]){"OLDPWD", cwd}, 0, all);
	}
	return (0);
}

int	handle_arg_cd(char **arg, char *cwd, t_all *all)
{
	char	*new_dir;

	new_dir = ft_malloc(PATH_MAX, 0, all);
	if (!new_dir)
		return (1);
	if (arg[1][0] == '-')
		arg[1] = get_value(all->env, "OLDPWD");
	if (arg[1][ft_strlen(arg[1]) - 1] == '\\' && arg[2])
	{
		arg[1] = ft_strjoin(ft_substr(arg[1], 0, \
		ft_strlen(arg[1]) - 1, all), " ", all);
		arg[1] = ft_strjoin(arg[1], arg[2], all);
	}
	if (chdir(arg[1]) == -1)
	{
		all->tmp = ft_strjoin("minibash: cd: ", arg[1], all);
		(all->tmp = ft_strjoin(all->tmp, ": ", all));
		return (all->error = ft_strjoin(all->tmp, strerror(errno), all), \
		exit_stat(1, 1), 1);
	}
	getcwd(new_dir, PATH_MAX);
	change_val(&all->env, (char *[]){"PWD", new_dir}, 0, all);
	change_val(&all->env, (char *[]){"OLDPWD", cwd}, 0, all);
	free(new_dir);
	return (0);
}

static void	move_to_parrent(char *env_path, int *i, int *flag)
{
	int	k;

	if (env_path[*i - 2] == '.' && env_path[*i - 1] == '.')
	{
		*flag = 1;
		k = 0;
		while (i > 0 && k < 2)
		{
			if (env_path[*i] == '/')
				k++;
			(*i)--;
		}
	}
	while (*i > 0 && env_path[*i] != '/')
		(*i)--;
}

int	handle_parrent_directory(char *env_path, int i, int flag, t_all *all)
{
	char	*tmp;
	char	*new_cwd;

	move_to_parrent(env_path, &i, &flag);
	tmp = ft_substr(env_path, 0, i, all);
	if (access(tmp, F_OK) == -1)
	{
		if (!flag)
		{
			new_cwd = ft_strjoin(get_value(all->env, "PWD"), "/..", all);
			change_val(&all->env, (char *[]){"PWD", new_cwd}, 0, all);
			change_val(&all->env, (char *[]){"OLDPWD", env_path}, 0, all);
		}
		return (all->error = "cd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory", \
		exit_stat(0, 1), 1);
	}
	if (chdir(tmp) == -1)
		return (all->error = strerror(errno), exit_stat(1, 1), 1);
	return (0);
}
