/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 07:44:52 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/14 15:52:21 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	get_cd_error(char *path, char *file)
{
	int			error;
	struct stat	stat;

	error = access(path, F_OK);
	if (error == -1)
	{
		free(path);
		return (ft_putend(file, " : No such file or directory.\n"));
	}
	if (lstat(path, &stat) == -1)
	{
		free(path);
		return ;
	}
	if (!S_ISDIR(stat.st_mode))
	{
		free(path);
		return (ft_putend(file, " : Not a directory.\n"));
	}
	error = access(path, R_OK);
	if (error == -1)
	{
		free(path);
		return (ft_putend(file, " : Permission denied.\n"));
	}
}

void		ft_cut_path(char *pwd)
{
	int		count;
	int		pos;
	int		i;

	count = 0;
	pos = 0;
	i = -1;
	while (pwd[++i])
	{
		if (pwd[i] == '/' && count <= pos)
			count = i;
		else if (pwd[i] == '/' && pos < count)
			pos = i;
	}
	pwd[pos > count ? pos : count] = '\0';
}

static void	change_dir(char ***env, char *cmd, char *buff, int is_path)
{
	char	*path;
	char	*pwd;
	char	tmp[4097];

	path = !is_path && cmd[0] != '/' ? ft_strjoin(buff, "/") : ft_strdup(cmd);
	if (!is_path && cmd[0] != '/')
		path = ft_strjoinfree(path, cmd, 1);
	if (chdir(path) == -1)
		return (get_cd_error(path, cmd));
	getcwd(tmp, 4096);
	pwd = ft_strjoin("PWD=", tmp);
	ft_setenv(env, pwd, 2);
	free(pwd);
	pwd = ft_strjoin("OLDPWD=", buff);
	ft_setenv(env, pwd, 2);
	free(pwd);
	free(path);
}

void		ft_cd(char ***env, char **cmd)
{
	char	buff[4097];
	char	*str;

	getcwd(buff, 4097);
	if (!cmd[1] || ft_strcmp(cmd[1], "--") == 0 || ft_strcmp(cmd[1], "-") == 0)
	{
		if (!(str = get_env(*env, (!cmd[1] || ft_strcmp(cmd[1], "--") == 0
					? "HOME" : "OLDPWD"))))
			return (ft_putendl("Something happend, path not in the pwd."));
		if (cmd[1] && ft_strcmp(cmd[1], "-") == 0 && chdir(str) != -1)
			ft_putendl(str);
		change_dir(env, str, buff, 1);
		free(str);
	}
	else if (!cmd[2])
		change_dir(env, cmd[1], buff, 0);
	else if (!cmd[3])
	{
		if (!(str = replace_str(buff, cmd[1], cmd[2])))
			return (ft_putend(cmd[1], " : not in the pwd.\n"));
		change_dir(env, str, buff, 1);
		free(str);
	}
}
