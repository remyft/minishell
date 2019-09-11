/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 12:02:53 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/14 12:16:41 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	cmp_strpart(char *src, char *str, int *beg)
{
	int i;

	i = 0;
	while (src[i] && src[i] == str[*beg] && src[i] != '=')
	{
		i++;
		*beg += 1;
	}
	if (src[i] == '=')
		if (!str[*beg] || !ft_isalnum(str[*beg]))
			return (i);
	return (0);
}

static char	*test_var(char **env, char *cmd)
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
		if ((to_cp = cmp_strpart(env[i], cmd, &end)))
		{
			ret = ft_strnew(to_cp + 2);
			ret[0] = '$';
			ft_strncpy(ret + 1, env[i], to_cp);
			ret[to_cp + 1] = '\0';
			return (ret);
		}
		i++;
	}
	return (NULL);
}

static int	deal_dollar(char **env, char **cmd, int i)
{
	char	*tmp;
	char	*var;
	char	*rep;

	if (!(tmp = test_var(env, cmd[i])))
	{
		ft_putend(ft_strstr(cmd[i], "$") + 1,
				" : Undefined variable.\n");
		return (0);
	}
	else
	{
		var = ft_strdup(cmd[i]);
		free(cmd[i]);
		rep = get_env(env, &tmp[1]);
		cmd[i] = replace_str(var, tmp, rep);
		free(tmp);
	}
	return (1);
}

int			get_var(char **env, char **cmd)
{
	int		i;
	char	*tmp;
	char	*tmp_cmd;

	i = -1;
	while (cmd[++i])
		if (ft_occuc(cmd[i], '$') && ft_strlen(cmd[i]) >= 2)
		{
			if (!deal_dollar(env, cmd, i))
				return (0);
		}
		else if (env[0] && cmd[i][0] == '~' && (cmd[i][1] == '/' || !cmd[i][1]))
		{
			if (!(tmp = get_env(env, "HOME")))
				return (0);
			tmp_cmd = ft_strdup(cmd[i]);
			free(cmd[i]);
			cmd[i] = replace_str(tmp_cmd, "~", tmp);
			free(tmp);
			free(tmp_cmd);
		}
	return (1);
}
