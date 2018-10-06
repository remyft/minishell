/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:53:59 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/06 14:59:15 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdio.h>

int		cmp_strpart(char *src, char *str, int *beg)
{
	int i;

	i = 0;
	while (src[i] && src[i] == str[*beg] && src[i] != '=')
	{
		i++;
		*beg += 1;
	}
	if (src[i] == '=')
		if (!str[*beg + 1] || !ft_isalnum(str[*beg + 1]))
			return (i);
	return (0);
}

char	*test_var(char **env, char *cmd)
{
	int		beg;
	int		end;
	int		to_cp;
	int		i;
	char	*ret;

	beg = 0;
	while (cmd[beg] != '$')
		beg++;
	beg++;
	i = 0;
	while (env[i])
	{
		end = beg;
		if (!(to_cp = cmp_strpart(env[i], cmd, &end)))
			i++;
		else
		{
			ret = ft_strnew(to_cp + 2);
			ret[0] = '$';
			ft_strncpy(ret + 1, env[i], to_cp);
			ret[to_cp + 1] = '\0';
			return (ret);
		}
	}
	return (NULL);
}

int		get_var(char **env, char **cmd)
{
	int		i;
	char	*tmp;
	char	*var;
	char	*rep;

	i = -1;
	while (cmd[++i])
		if (ft_occuc(cmd[i], '$'))
		{
			if (!(tmp = test_var(env, cmd[i])))
			{
				ft_putend(ft_strstr(cmd[i], "$"), " : Undefined variable.");
				return (0);
			}
			else
			{
				var = ft_strdup(cmd[i]);
				free(cmd[i]);
				cmd[i] = replace_str(var, tmp, (rep = get_env(env, &tmp[1])));
				//free(tmp);
			}
		}
		else if (cmd[i][0] == '~')
		{
			tmp = get_env(env, "HOME");
			free(cmd[i]);
			cmd[i] = ft_strdup(tmp);
			free(tmp);
		}
	return (1);
}

int		main(int ac, char **av, char **ep)
{
	char	*line;
	char	*env[100];
	int		i;
	char	**parse;
	char	buff[4097];

	i = 0;
	(void)ac;
	(void)av;
	env[0] = get_env(ep, "HOME");
	while (ep[++i])
		env[i] = ft_strdup(ep[i]);
	env[i] = NULL;
	line = NULL;
	while (1)
	{
		ft_putend(getcwd(buff, 4097), "$> ");
		line = get_line(1);
		parse = ft_strsplit_ws(line);
		if (parse)
		{
			if (!(get_var(env, parse)))
				continue ;
			deal_cmd(parse, env);
			i = 0;
			while (parse[i])
				free(parse[i++]);
			free(parse);
		}
		if (line)
			free(line);
	}
	return (0);
}
