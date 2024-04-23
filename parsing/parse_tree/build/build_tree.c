/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:07:21 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/23 04:06:53 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static t_tree	*add_branch(char **l_r, t_e_oper oper, int *doc_i, t_all *all)
{
	t_tree	*tree;
	// char	**pre_env_arr;

	tree = ft_malloc(sizeof(t_tree), 0, all);
	if (!tree)
		return (NULL);
	*tree = (t_tree){0};
	if (oper)
	{
		tree->oper = oper;
		tree->output = 1;
	}
	else
	{
		tree->cmd_str = ft_strdup(l_r[0], all);
		tree->doc_i = *doc_i;
		// pre_env_arr = split_by_space(l_r[0], error);
		// get_environment(&(l_r[0]), error);
		// tree->cmd = split_by_space(l_r[0], error);
		// get_wildcard(tree->cmd, error);
		// tree->input = get_input_output(tree->cmd, 0, pre_env_arr, error);
		// tree->output = get_input_output(tree->cmd, 1, pre_env_arr, error);
		// tree->here_doc = get_here_doc(l_r[0], &tree->input, *doc_i, error);
		// printf("doc_i----> %d\n", *doc_i);
		(*doc_i)++;
	}
	return (tree);
}

static void	handle_parentheses(void **data, t_all *all, t_e_oper opr, int *doc_i)
{
	char	*str;
	t_tree	**tree;
	t_tree	**root;

	str = data[0];
	tree = data[1];
	root = data[2];
	*tree = add_branch(NULL, opr, doc_i, all);
	if (!(*root) && !all->error)
		*root = *tree;
	if (all->error)
		return ;
	str = split_by_parantheses(str, all);
	if (all->error || !str)
		return ;
	(*tree)->here_doc = get_here_doc(str, &(*tree)->input, *doc_i, all);
	if (!str)
		return ;
	build_tree(str, (t_tree **[2]){&(*tree)->left, root}, all, doc_i);
}

void    build_tree(char *str, t_tree **tree_root[2], t_all *all, int *doc_i)
{
	t_tree		**tree;
	t_tree		**root;
	char		**l_r;
	t_e_oper		oper;
	
	tree = tree_root[0];
	root = tree_root[1];
	if (all->error)
		return ;
	oper = split_cmds_queue(str, &l_r, all);
	if (oper == PARENTHESES)
	{
		handle_parentheses((void *[3]){str, tree, root}, all, oper, doc_i);
		return ;
	}
	*tree = add_branch(l_r, oper, doc_i, all);
	if (!(*root) && !all->error)
		*root = *tree;
	if (str && (*tree)->oper && !all->error)
	{
		build_tree(l_r[0], (t_tree **[2]){&(*tree)->left, root}, all, doc_i);
		build_tree(l_r[1], (t_tree **[2]){&(*tree)->right, root}, all, doc_i);
	}
}
