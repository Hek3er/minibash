/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:26:55 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/06 14:06:12 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	close_fd(t_all_fd *all_fd, int fd)
{
	while (all_fd)
	{
		if (all_fd->fd == fd)
		{
			close(all_fd->fd);
			all_fd->fd = -1;
			// return ;
		}
		all_fd = all_fd->next;
	}
}

static void	close_all_fd(t_all_fd *all_fd)
{
	all_fd = all_fd->next;
	while (all_fd)
	{
		if (all_fd->fd > 1)
			close(all_fd->fd);
		all_fd = all_fd->next;
	}
}

static int	append_fd(t_all_fd *all_fd, int fd, t_all *all)
{
	t_all_fd	*node;

	node = ft_malloc(sizeof(t_all_fd), 0, all);
	if (!node)
		return (1);
	node->fd = fd;
	node->next = NULL;
	while (all_fd->next)
		all_fd = all_fd->next;
	all_fd->next = node;
	return (0);
}

static char	*wildcard_expand(char *path, t_all *all)
{
	char	**arr;
	arr = get_wildcard((char *[]){path, NULL}, all);
	if (arr && arr[0])
		return (arr[0]);
	else
		return (path);
}

int	ft_open(char *path, t_e_open_modes mode, t_all *all, int close_mode)
{
	static t_all_fd	all_fd = {-1, NULL};
	int				fd;
	int				flags;

	flags = 0;
	if (close_mode > 1)
		return (close_fd(&all_fd, close_mode), -1);
	if (close_mode == 1)
		return (close_all_fd(&all_fd), all_fd.next = NULL, 0);
	if (mode == OPEN_TRUNC)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else if (mode == OPEN_APPEND)
		flags = O_CREAT | O_APPEND | O_WRONLY;
	else if (mode == OPEN_READ)
		flags = O_RDONLY;
	fd = open(wildcard_expand(path, all), flags, 0777);
	if (fd < 0 || append_fd(&all_fd, fd, all))
	{
		ft_write("minibash: ", 2, 0);
		ft_write(path, 2, 0);
		ft_write(": ", 2, 0);
		all->error = ft_strdup(strerror(errno), all);
		exit_stat(1, 1);
	}
	return (fd);
}
