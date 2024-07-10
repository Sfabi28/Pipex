/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:59:36 by sfabi             #+#    #+#             */
/*   Updated: 2024/02/19 10:03:16 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
void	child(int fds, char **argv, char **env, int arr[2]);
void	child2(int fds, char **argv, char **env, int arr[2]);
void	ft_perror(char	*str);
char	*get_path(char *cmd, char **env);

#endif
