/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 19:12:24 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/02 19:14:24 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**parse_line(char **parsed, char *cmd)
{
	int		nb_char;
	int		i;
	int		j;

	i = 0;
	while (*cmd)
	{
		nb_char = 0;
		if (*cmd > 13 && *cmd != 32)
		{
			while (*(cmd + nb_char) > 13 && *(cmd + nb_char) != 32)
				nb_char++;
			if (!(parsed[i] = (char*)ft_memalloc(sizeof(char) * nb_char + 1)))
				return (NULL);
			j = -1;
			while (*cmd > 13 && *cmd != 32 && (j = j + 1) > -1)
				parsed[i][j] = *cmd++;
			i++;
		}
		else
			cmd++;
	}
	parsed[i] = NULL;
	return (parsed);
}

char		**parsing(char *cmd)
{
	int		ws;
	char	**parsed;
	char	*curr;

	ws = 0;
	if (!*cmd)
		return (NULL);
	curr = cmd;
	while (*curr)
	{
		if (*curr > 13 && *curr != 32)
			ws++;
		else if (*curr == ' ')
		{
			while (*curr == ' ')
				curr++;
			if (curr)
				ws++;
		}
		curr++;
	}
	if (!(parsed = (char**)ft_memalloc(sizeof(char *) * (ws + 1))))
		return (NULL);
	return (parse_line(parsed, cmd));
}
