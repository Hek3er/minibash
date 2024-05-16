/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:23:43 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/25 10:55:01 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static int	count(char const *s, char c)
{
	int	check;
	int	count;
	int	i;

	check = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			check += 1;
			if (check == 1)
				count += 1;
		}
		else
			check = 0;
		i++;
	}
	return (count);
}

static char	**fill(char **ptr, char const *s, char c, t_all *all)
{
	int	len;
	int	i;
	int	first_occ;

	len = 0;
	i = 0;
	while (s[len])
	{
		if (s[len] == c)
		{
			len++;
			continue ;
		}
		first_occ = len;
		while (s[len] != c && s[len])
			len++;
		ptr[i] = ft_malloc(sizeof(char) * (len - first_occ + 1), 0, all);
		if (!ptr[i])
			return (NULL);
		ft_strlcpy(ptr[i], (s + first_occ), (len - first_occ + 1));
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c, t_all *all)
{
	int		n_words;
	int		i;
	char	**ptr;

	i = 0;
	if (!s)
		return (NULL);
	n_words = count(s, c);
	ptr = ft_malloc(sizeof(char *) * (n_words + 1), 0, all);
	if (!ptr)
		return (NULL);
	if (!fill(ptr, s, c, all))
	{
		while (ptr[i])
		{
			free (ptr[i]);
			i++;
		}
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
