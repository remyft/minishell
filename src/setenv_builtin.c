/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 07:43:19 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/14 11:15:47 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	cmp_env(char *env, char *new)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!ft_occuc(new, '='))
		tmp = ft_strjoin(new, "=");
	else
		tmp = ft_strdup(new);
	while (env[i] && env[i] == tmp[i] && env[i] != '=')
		i++;
	if (i != 0 && env[i] == '=' && env[i] == tmp[i])
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char		*get_env(char **env, char *to_get)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i] && !cmp_env(env[i], to_get))
		i++;
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

static int	check_var(char *var)
{
	int i;

	i = 0;
	if (ft_isdigit(var[0]))
	{
		ft_putendl("setenv : Variable name must begin with a letter.");
		return (1);
	}
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]))
		{
			ft_putstr("setenv : Variable name must contain alphanumeric");
			ft_putendl(" characters.");
			return (1);
		}
		i++;
	}
	return (0);
}

void		ft_setenv(char ***env, char *new, int len)
{
	int i;

	if (check_var(new) == 1)
		return ;
	i = -1;
	if (len == 2 && ft_occuc(new, '='))
	{
		while ((*env)[++i])
			if (ft_strcmp((*env)[i], new) == 0)
				return ;
			else if (cmp_env((*env)[i], new))
			{
				free((*env)[i]);
				(*env)[i] = ft_strdup(new);
				return ;
			}
		*env = ft_ralloc(env, 1);
		(*env)[i] = ft_strdup(new);
		(*env)[++i] = NULL;
	}
	else if (len != 2)
		ft_putendl("setenv : Too many arguments");
}

void		ft_unsetenv(char ***env, char **unset)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	k = 0;
	while (unset[++k])
	{
		i = 0;
		j = -1;
		while ((*env)[++j])
			if (!(cmp_env((*env)[j], unset[k])))
			{
				tmp = ft_strdup((*env)[j]);
				if ((*env)[i])
					free((*env)[i]);
				(*env)[i] = NULL;
				(*env)[i] = ft_strdup(tmp);
				free(tmp);
				i++;
			}
		if (i != j)
			*env = ft_ralloc(env, -1);
	}
}
