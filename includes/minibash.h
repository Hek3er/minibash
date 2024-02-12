/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibash.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:01:52 by azainabi          #+#    #+#             */
/*   Updated: 2024/02/12 07:13:52 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIBASH_H
# define MINIBASH_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_var
{
	int		i;
	int		j;
	int		rem;
	char	*tmp_key;
	char	*tmp_val;
}				t_var;

/*
 * Functions
*/

char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);

/*
 * Error
*/
void	error_exit(char *str, int x);

/*
 * Parse_env
*/

void	append_node(t_env **head, char *key, char *value);
t_env	*parse_env(char **env);

#endif