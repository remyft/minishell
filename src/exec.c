/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:15:36 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/06 19:39:25 by rfontain         ###   ########.fr       */
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

static char	*get_path(char **env, char *cmd)
{
	char		*toget;
	char		*path;
	int			i;
	struct stat	stat;

	toget = get_env(env, "PATH");
	while (1)
	{
		i = 0;
		if (!(path = malloc(sizeof(char) * (ft_strlen_ch(toget, ':') + 1))))
			return (NULL);
		while (toget[i] && toget[i] != ':')
		{
			path[i] = toget[i];
			i++;
		}
		path[i] = '\0';
		path = ft_strjoinfree(path, "/", 1);
		path = ft_strjoinfree(path, cmd, 1);
		if (lstat(path, &stat) != -1)
			return (path);
		free(path);
		if (!ft_occuc(toget, ':'))
			return (NULL);
		toget += !(toget + ft_strlen_ch(toget, ':')) ? ft_strlen_ch(toget, ':') : ft_strlen_ch(toget, ':') + 1;
	}
	return (NULL);
}

int			ft_exec(char **env, char **cmd)
{
	pid_t	pid;
	char	*path;
	int		status;

	if (!(path = get_path(env, cmd[0])))
		return (0);
	free(cmd[0]);
	cmd[0] = ft_strdup(path);
	free(path);
	pid = fork();
	if (pid < 0)
	{
		free(path);
		return (0);
	}
	else if (pid == 0)
	{
		execve(cmd[0], cmd, env);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	return (1);
}
