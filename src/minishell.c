/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:53:59 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/28 20:54:35 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(char **env)
{
	int i;

	i = 0;
	while (env[i])
		free(env[i++]);
	exit(0);
}

void	deal_cmd(char *cmd, char **env)
{
	int i;

	i = 0;
	if (ft_strcmp(cmd, "env") == 0)
		while (env[i])
			ft_putendl(env[i++]);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(env);
}

int		main(int ac, char **av, char **ep)
{
	char *line;
	char *env[100];
	int i;

	i = -1;
	(void)ac;
	(void)av;
	while (ep[++i])
		env[i] = ft_strdup(ep[i]);
	env[i] = NULL;
	while (1)
	{
		ft_putstr("<$ ");
		get_next_line(1, &line);
		deal_cmd(line, env);
	}
	return (0);
}
