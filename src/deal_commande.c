/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_commande.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 19:17:15 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/03 19:44:21 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_echo(char **cmd, int len)
{
	int i;

	i = 1;
	if (len == 1)
		return (ft_putchar('\n'));
	if (len == 2 && cmd[1][0] != '-')
		ft_putendl(cmd[1]);
	else if (cmd[1][0] == '-' && cmd[1][1] && cmd[1][1] == 'n' && !cmd[1][2])
	{
		while (++i < len)
			ft_putend(cmd[i], i == len - 1 ? "" : " ");
	}
	else if (len > 2)
	{
		while (i < len)
		{
			ft_putstr(cmd[i]);
			ft_putstr(i++ == len - 1 ? "" : " ");
		}
		ft_putchar('\n');
	}
}

static int	cmp_env(char *env, char *new)
{
	int i;

	i = 0;
	while (env[i] == new[i] && env[i] != '=')
		i++;
	if (env[i] == '=')
		return (1);
	return (0);
}

static void	ft_setenv(char **env, char *new, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (len == 2)
	{
		while (env[i])
		{
			if (ft_strcmp(env[i], new) == 0)
				return ;
			else if (cmp_env(env[i], new))
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
	else
		ft_putendl("setenv : Too many arguments");
}

static void	ft_exit(char **env, char *ex, int len)
{
	int i;
	int	val;

	if (len <= 2)
	{
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
	else
		ft_putendl("exit : Expression Syntax");
}

void		deal_cmd(char **cmd, char **env)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(env, cmd[1], i);
	else if ((ft_strcmp(cmd[0], "env") == 0 ||
				(ft_strcmp(cmd[0], "setenv") == 0 && i == 1)) && (i = 0) > -1)
		while (env[i])
			ft_putendl(env[i++]);
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		ft_setenv(env, cmd[1], i);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd, i);
}
