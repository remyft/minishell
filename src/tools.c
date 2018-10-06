/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 05:48:08 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/06 15:05:26 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_line(int fd)
{
	char	buff[4097];
	int		nb_read;
	int		i;

	nb_read = read(fd, buff, 4097);
	buff[nb_read] = '\0';
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	buff[i] = '\0';
	if (buff[0])
		return (ft_strdup(buff));
	else
		return (NULL);
}

char	*replace_str(char *path, char *src, char *replace)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*str;

	if (!ft_strstr(path, src))
		return (NULL);
	i = 0;
	j = 0;
	ft_find(path, src, &i, &j);
	if (!(str = malloc(sizeof(char) * (ft_strlen(path) - ft_strlen(src)
						+ ft_strlen(replace) + 1))))
		return (NULL);
	k = -1;
	while (++k < i)
		str[k] = path[k];
	str[k] = '\0';
	l = -1;
	while (replace[++l])
		str[k + l] = replace[l];
	k--;
	while (path[++k + j])
		str[k + l] = path[k + j];
	str[k + l] = '\0';
	return (str);
}