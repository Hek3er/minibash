/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:39:46 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/08 11:22:32 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static void	set_heredocs(t_tree *root, t_all *all)
{
	if (root != NULL)
	{
		if (root->cmd_str)
			get_cmd_info(root, all);
		set_heredocs(root->left, all);
		set_heredocs(root->right, all);
	}
}

int	parse_tree(char *s, t_all *all)
{
	t_tree	*root;
	int		doc_i;

	root = NULL;
	doc_i = 0;
	all->add_quotes_to_env = 0;
	if ((check_q_p(s, all), all->error) || \
		(check_here_doc(s, all), all->error) || \
		(check_opers(s, all), all->error) || \
		(adjust_redirectionals(&s, all), all->error) || \
		(build_tree(s, (t_tree **[2]){&all->tree, &root}, all, &doc_i), \
		all->error))
		return (all->tree = root, 1);
	all->tree = root;
	set_heredocs(root, all);
	return (0);
}
