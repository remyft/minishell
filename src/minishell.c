/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:53:59 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/14 14:39:06 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**collect_env(char **ep)
{
	char	**env;
	char	*tmp;
	int		ntmp;
	int		i;

	i = -1;
	if (!(env = (char**)malloc(sizeof(char*) * (get_tab_len(ep)
						+ 1))))
		return (NULL);
	while (ep[++i])
		env[i] = ft_strdup(ep[i]);
	env[i] = NULL;
	if (!(tmp = get_env(env, "SHLVL")))
		ntmp = 0;
	else
	{
		ntmp = ft_atoi(tmp);
		free(tmp);
	}
	tmp = ft_strjoinfree("SHLVL=", ft_itoa(ntmp + 1), 2);
	ft_setenv(&env, tmp, 2);
	free(tmp);
	return (env);
}

void	parsing(char ***env)
{
	char	*line;
	int		i;
	char	**parse;
	char	**cmd;

	line = get_line(0);
	parse = NULL;
	if (line)
		parse = ft_strsplit(line, ';');
	i = -1;
	while (parse && parse[++i])
	{
		cmd = ft_strsplit_ws(parse[i]);
		if (!(get_var(*env, cmd)))
			return ;
		if (cmd[0])
			deal_cmd(cmd, env);
		free_tab(&cmd);
	}
	if (parse)
		free_tab(&parse);
	if (line)
		free(line);
}

int		main(int ac, char **av, char **ep)
{
	char	**env;
	char	prompt[4097];

	(void)ac;
	(void)av;
	if (!(env = collect_env(ep)))
	{
		if (!(env = (char**)malloc(sizeof(char*))))
			return (-1);
		env[0] = NULL;
	}
	while (1)
	{
		ft_putstr(RESET);
		if (getcwd(prompt, 4097))
			ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,
					" $> ", BLUE);
		else
			ft_putstr_cl("$> ", BLUE);
		ft_putstr(WHITE);
		parsing(&env);
	}
	return (0);
}
