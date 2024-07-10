/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:59:36 by sfabi             #+#    #+#             */
/*   Updated: 2024/02/19 11:38:48 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/mman.h>
# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

int		free_split(char **map);
void	ft_perror(char	*str);
char	*get_path(char *cmd, char **env);
void	child(char *argv, char **env);
int		command(char *argv, char **env);
void	ft_heredoc(char **argv);
int		read_gnl(char **line);
int		ft_free(char *s);
void	ft_here_doc(char **argv);

#endif
