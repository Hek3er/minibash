/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:39:46 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/23 04:03:21 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"
	// int order = 0;

// void printTree(t_tree *root, int level)
// {
// 	if (root == NULL)
// 		return;

// 	printTree(root->left, level + 1);

// 	for (int i = 0; i < level; i++)
// 		printf("    ");

// 	if (root->cmd_str)
// 	{
// 		order++;
// 		printf("%s(%d)\n", root->cmd_str, order);
// 	}
// 	else if (root->oper)
// 		printf("%d(%d)\n", root->oper, order);

// 	printTree(root->right, level + 1);
// }

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

// void printTree(t_tree *root, int i, char *str, t_all *all) {
// 	if (root != NULL) 
// 	{
// 		if (root->cmd_str)
// 		{
// 			get_cmd_info(root, all);
// 			if (all->error)
// 				printf("%s\n", all->error);
// 			// printf("%d ",root->oper);
// 			while(*(root->cmd))
// 			{
// 				printf("%s ",*(root->cmd));
// 				(root->cmd)++;
// 			}
// 			// printf("\n");
// 		}
// 		if (root->oper)
// 			printf("%d ",root->oper);
// 		printTree(root->left, i + 1, "left", all);
// 		printTree(root->right, i + 1, "right", all);
// 	}
// }
//***************************************************
int    parse_tree(char *s, t_all *all)
{
	t_tree  *root;
	int		doc_i;

	root = NULL;
	doc_i = 0;
	if ((check_here_doc(s, all), all->error) || \
		(check_q_p(s, all), all->error) || \
		(check_opers(s, all), all->error) || \
		(s = adjust_redirectionals(s, all), all->error) || \
		(build_tree(s, (t_tree **[2]){&all->tree, &root}, all, &doc_i), all->error))
		return (all->tree = root, 1);
	all->tree = root;
	set_heredocs(root, all);
	// printTree(root, 0, "start", all);
	// printTree(root, 0);
	// printf("\n");
	return (0);
}
// int	main()
// {
// 	char	*error;
// 	t_all	all;

// 	error = NULL;

// 	parse_tree("test1 || <<hello test2 &&(test1 | test2 &&(hi))", &all, &error);
// 	remove_docs(&error);
// 	ft_open(NULL, 0, NULL, 1);
// 	ft_malloc(0, 1, NULL);


// 	parse_tree("<a ||hello 1", &all, &error);
// 	remove_docs(&error);
// 	ft_open(NULL, 0, NULL, 1);
// 	ft_malloc(0, 1, NULL);
// 	while (1);
// }