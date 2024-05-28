/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:24:12 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/17 02:56:51 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static char	*find_cmd_path(char **paths, char *cmd, t_all *all)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (paths[i] && cmd[0])
	{
		cmd_path = ft_strjoin(paths[i], "/", all);
		cmd_path = ft_strjoin(cmd_path, cmd, all);
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_all *all, char *cmd)
{
	char	*env_path;
	char	**paths;
	char	*cmd_path;

	if (strchr(cmd, '/'))
		return (cmd);
	env_path = get_value(all->env, "PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':', all);
	if (!paths)
		return (NULL);
	cmd_path = find_cmd_path(paths, cmd, all);
	return (cmd_path);
}
