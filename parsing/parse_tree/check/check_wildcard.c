/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:11:13 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/27 10:42:03 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static void	handle_star(char **file, char **patt)
{
	if (**patt == '*')
	{
		while (**patt && **patt == '*')
			(*patt)++;
		while (**file && **file != **patt)
			(*file)++;
	}
}

static int	validate_wildcard(char *file, char *patt)
{
	char	*original_patt;
	original_patt = patt;

	if (*patt != '*' && *file != *patt)
		return (0);
	handle_star(&file, &patt);
	while (*patt && *patt == *file)
		(file++ && patt++);
	if (*file && *patt == '*')
		return (validate_wildcard(file, patt));
	if (*file && *patt && *patt != *file)
		return (validate_wildcard(file, original_patt));
	if (*patt == '*')
		return (validate_wildcard(file, patt));
	if (!*patt && !*file)
		return (1);
	return (0);
}

int	check_wildcard(char *file, char *patt)
{
	if (*patt == '.' && *file != '.')
		return (0);
	else if (*patt != '.' && *file == '.')
		return (0);
	return (validate_wildcard(file, patt));
}
