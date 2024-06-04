/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:39:46 by ealislam          #+#    #+#             */
/*   Updated: 2024/06/04 22:31:29 by azainabi         ###   ########.fr       */
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


void printTree(t_tree *root, int i, char *str, t_all *all) {
	if (root != NULL) 
	{
		if (root->oper)
			// printf("%d \n", root->oper);
			printf("in %d %s tree_node operator %d:(out %d in %d h_doc %d)\n\n",i ,str, root->oper, root->output, root->input, root->here_doc);
		if (root->cmd_str)
		{
			get_cmd_info(root, all);
			if (all->error)
				printf("%s\n", all->error);
			printf("in %d %s tree_node operator is : %d :(out %d in %d h_doc %d)\n",i, str, root->oper, root->output, root->input, root->here_doc);
			if (root->oper!= 0)
				printf("%d \n", root->oper);
			while(*(root->cmd))
			{
				printf("{%s} \n",*(root->cmd));
				(root->cmd)++;
			}
			printf("\n");
		}
		printTree(root->left, i + 1, "left", all);
		printTree(root->right, i + 1, "right", all);
	}
}

int	parse_tree(char *s, t_all *all)
{
	t_tree	*root;
	int		doc_i;

	root = NULL;
	doc_i = 0;
	if ((check_here_doc(s, all), all->error) || \
		(check_q_p(s, all), all->error) || \
		(check_opers(s, all), all->error) || \
		(adjust_redirectionals(&s, all), all->error) || \
		(build_tree(s, (t_tree **[2]){&all->tree, &root}, all, &doc_i), \
		all->error))
		return (all->tree = root, 1);
	all->tree = root;
	// printTree(root, 0, "start", all);
	set_heredocs(root, all);
	return (0);
}
