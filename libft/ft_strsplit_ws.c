/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_ws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 07:55:26 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/08 19:00:02 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_countw(const char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] >= 8 && str[i] <= 13) || str[i] == 32))
			i++;
		if (str[i] && !((str[i] >= 8 && str[i] <= 13) || str[i] == 32))
		{
			count++;
			while (str[i] && !((str[i] >= 8 && str[i] <= 13) || str[i] == 32))
				i++;
		}
	}
	return (count);
}

static	int		ft_strlensp(const char *str)
{
	int i;

	i = 0;
	while (!((*str >= 8 && *str <= 13) || *str == 32))
	{
		if (*str == '\0')
			break ;
		str++;
		i++;
	}
	return (i);
}
#include <stdio.h>
char			**ft_strsplit_ws(char const *s)
{
	char	**split;
	int		k;
	int		nbword;

	if (s == NULL)
		return (NULL);
	if ((split = (char**)malloc(sizeof(char*) * (ft_countw(s) + 1))) == NULL)
		return (NULL);
	nbword = ft_countw(s);
	split[nbword + 1] = 0;
	k = 0;
	while (nbword--)
	{
		while ((*s >= 8 && *s <= 13) || *s == 32)
			s++;
		if (*s && !((*s >= 8 && *s <= 13) || *s == 32))
		{
			printf("%d\n", ft_strlensp(s));
			if ((split[k] = ft_strsub(s, 0, ft_strlensp(s))) == NULL)
				return (NULL);
			s += ft_strlensp(s) + 1;
			k++;
		}
	}
	split[k] = NULL;
	return (split);
}
