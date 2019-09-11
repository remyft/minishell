/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:15:36 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/14 10:18:26 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_strlen_ch(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_strccpy(char *toget, char *cmd, char c, int j)
{
	int		i;
	char	*path;

	i = 0;
	if (!(path = malloc(sizeof(char) * (ft_strlen_ch(&toget[j], c) + 1))))
		return (NULL);
	while (toget[i + j] && toget[i + j] != c)
	{
		path[i] = toget[i + j];
		i++;
	}
	path[i] = '\0';
	path = ft_strjoinfree(path, "/", 1);
	path = ft_strjoinfree(path, cmd, 1);
	return (path);
}

static char	*get_path(char **env, char *cmd)
{
	char		*toget;
	char		*path;
	int			j;
	struct stat	stat;

	j = 0;
	toget = get_env(env, "PATH");
	while (1 && toget)
	{
		path = ft_strccpy(toget, cmd, ':', j);
		if (lstat(path, &stat) != -1)
		{
			free(toget);
			return (path);
		}
		free(path);
		if (!ft_occuc(&toget[j], ':'))
		{
			free(toget);
			return (NULL);
		}
		j += !(toget[j + ft_strlen_ch(toget, ':')])
			? ft_strlen_ch(&toget[j], ':') : ft_strlen_ch(&toget[j], ':') + 1;
	}
	return (NULL);
}

void		deal_fork(char **env, char **cmd)
{
	if (execve(cmd[0], cmd, env) == -1)
		ft_putend(cmd[0], " : command not found.\n");
	free_tab(&env);
	free_tab(&cmd);
	exit(0);
}

int			ft_exec(char **env, char **cmd)
{
	pid_t	pid;
	char	*path;
	int		status;

	if (cmd[0][0] != '/' && cmd[0][0] != '.')
	{
		if (!(path = get_path(env, cmd[0])))
			return (0);
		free(cmd[0]);
		cmd[0] = ft_strdup(path);
		free(path);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_putendl("Something happend, fork failed.");
		return (0);
	}
	else if (pid == 0)
		deal_fork(env, cmd);
	else if (pid > 0)
		waitpid(pid, &status, 0);
	return (1);
}
