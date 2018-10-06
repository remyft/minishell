/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 07:43:19 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/06 10:13:17 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	cmp_env(char *env, char *new)
{
	int i;

	i = 0;
	while (env[i] && env[i] == new[i] && env[i] != '=')
		i++;
	if (env[i] == '=')
		return (1);
	i = 0;
	return (0);
}

char		*get_env(char **env, char *to_get)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(to_get, "=");
	while (env[i] && !cmp_env(env[i], tmp))
		i++;
	free(tmp);
	tmp = NULL;
	if (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		tmp = ft_strdup(&env[i][j + 1]);
	}
	return (tmp);
}

void		ft_setenv(char **env, char *new, int len)
{
	int i;

	i = 1;
	if (len == 2)
	{
		while (env[i])
		{
			if (ft_strcmp(env[i], new) == 0)
				return ;
			else if (cmp_env(env[i], new))
			{
				free(env[i]);
				env[i] = !ft_occuc(new, '=') ? ft_strjoin(new, "=")
					: ft_strdup(new);
				return ;
			}
			i++;
		}
		env[i] = ft_occuc(new, '=') ? ft_strdup(new) : ft_strjoin(new, "=");
		env[++i] = NULL;
	}
	else
		ft_putendl("setenv : Too many arguments");
}

void	ft_unsetenv(char **env, char **unset)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;
	char	*funset;

	i = 1;
	j = 1;
	k = 0;
	while (unset[++k])
	{
		funset = ft_strjoin(unset[k], "=");
		while (env[j])
			if (cmp_env(env[j], funset))
				j++;
			else
			{
				tmp = ft_strdup(env[j]);
				free(env[i]);
				env[i] = ft_strdup(tmp);
				free(tmp);
				i++;
				j++;
			}
		free(funset);
		if (env[i])
			free(env[i]);
		env[i] = NULL;
	}
}
