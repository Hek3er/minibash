/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:02:14 by azainabi          #+#    #+#             */
/*   Updated: 2024/02/12 07:09:32 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minibash.h"
#include <string.h>
int	main(int ac, char **av, char **env)
{
	char	*line;

	t_env	*envirement = parse_env(env);
	for (int i = 0; env[i] != NULL; i++)
	{
		printf("%s \n ", env[i]);
	}
	printf("----------------------------------------\n");
	t_env *tmp = envirement;
	while (tmp)
	{
		if (strcmp(tmp->key, "_") == 0 )
		{
			printf("The key is : %s\n", tmp->key);
			printf("The value is : %s\n", tmp->value);
		}
		tmp = tmp->next;
	}
	// while (1)
	// {
	// 	line = readline("minibash ≥ ");		
	// }
}