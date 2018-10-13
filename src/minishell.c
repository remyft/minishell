/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:53:59 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/13 13:16:51 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (!(env = (char**)malloc(sizeof(char*) * 2)))
			return (-1);
		env[0] = ft_strdup("RIEN");
		env[1] = NULL;
	}
	while (1)
	{
		ft_putstr(RESET);
		ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,
				" $> ", BLUE);
		ft_putstr(WHITE);
		parsing(&env);
	}
	return (0);
}
