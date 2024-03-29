/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:49:03 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/13 12:05:13 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>

void	deal_cmd(char **cmd, char ***env);

char	*get_line(int fd);
char	*replace_str(char *path, char *src, char *replace);
void	free_tab(char ***tab);
int		get_tab_len(char **tab);
char	**ft_ralloc(char ***env, int len);

void	ft_setenv(char ***env, char *new, int len);
char	*get_env(char **env, char *to_get);
void	ft_unsetenv(char ***env, char **unset);
char	**collect_env(char **ep);

void	ft_cd(char ***env, char **cmd);

int		ft_exec(char **env, char **cmd);

int		get_var(char **env, char **cmd);

#endif
