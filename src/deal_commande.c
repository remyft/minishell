/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_commande.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 19:17:15 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/02 20:12:17 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_setenv(char **env, char *new)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], new) == 0)
			return ;
		else if (ft_strcmp(env[i], new) == '=')
		{
			free(env[i]);
			env[i] = ft_strdup(new);
			return ;
		}
		i++;
	}
	env[i] = ft_strdup(new);
	env[++i] = NULL;
}

static void	ft_exit(char **env, char *ex)
{
	int i;
	int	val;

	i = -1;
	val = 0;
	if (ex)
	{
		if (ex[0] == '-')
			i++;
		while (ex[++i])
			if (!ft_isdigit(ex[i]))
				return (ft_putendl("exit : Expression Syntax."));
		val = ft_atoi(ex);
	}
	i = 0;
	while (env[i])
		free(env[i++]);
	ft_putendl("exit");
	exit(val % 256);
}

void		deal_cmd(char **cmd, char **env)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	if (ft_strcmp(cmd[0], "exit") == 0)
	{
		if (i <= 2)
			ft_exit(env, cmd[1]);
		else
			ft_putendl("exit : Expression Syntax");
	}
	else if ((ft_strcmp(cmd[0], "env") == 0 || (ft_strcmp(cmd[0], "setenv") == 0 && i == 1))
			&& (i = 0) > -1)
		while (env[i])
			ft_putendl(env[i++]);
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		ft_setenv(env, cmd[1]);
}
