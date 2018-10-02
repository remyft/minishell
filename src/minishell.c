/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:53:59 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/02 20:13:15 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		main(int ac, char **av, char **ep)
{
	char	*line;
	char	*env[100];
	int		i;
	char	**parse;

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
		parse = parsing(line);
		deal_cmd(parse, env);
	}
	return (0);
}
