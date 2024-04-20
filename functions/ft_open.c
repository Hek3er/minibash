/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:26:55 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/19 03:39:08 by azainabi         ###   ########.fr       */
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
			return ;
		}
		all_fd = all_fd->next;
	}
}

static void	close_all_fd(t_all_fd *all_fd)
{
	all_fd = all_fd->next;
	while (all_fd)
	{
		// ft_write("closing fd\n", 2, 0);
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


int	ft_open(char *path, t_e_open_modes mode, t_all *all, int close_mode)
{
	static t_all_fd	all_fd = {-1, NULL};
	int				fd;
	int				flags;
	char			*tmp;

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
	fd = open(path, flags, 0777);
	if (fd < 0 || append_fd(&all_fd, fd, all))
	{
		ft_write("minibash: ", 2, 0);
		ft_write(path, 2, 0);
		ft_write(": ", 2, 0);
		// ft_write(strerror(errno), 2, 1);
		// tmp = ft_strjoin("Minibash: ", path, all);
		// tmp = ft_strjoin(tmp, " : ", all);
		all->error = ft_strdup(strerror(errno), all);
		// ft_write(all->error, 2, 1);
		// all->error = ft_strjoin(tmp, "dd", all);
		exit_stat(1, 1);
	}
	return (fd);
}
