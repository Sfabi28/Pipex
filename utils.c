/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:23:08 by sfabi             #+#    #+#             */
/*   Updated: 2024/02/12 16:22:45 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**split;
	char	*arr;
	char	*path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	split = ft_split(&env[i][5], ':');
	if (!split)
		return (NULL);
	i = -1;
	while (split[++i])
	{
		arr = ft_strjoin(split[i], "/");
		path = ft_strjoin(arr, cmd);
		free(arr);
		if (access(path, F_OK | X_OK) == 0 && free_split(split))
			return (path);
		free(path);
	}
	free_split(split);
	return (NULL);
}

void	ft_perror(char	*str)
{
	perror(str);
	exit(-1);
}

int	free_split(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	return (1);
}

int	read_gnl(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = ft_strdup(buffer);
	if (!(*line))
		return (free(buffer), -1);
	free(buffer);
	return (r);
}

int	ft_free(char *s)
{
	free(s);
	return (1);
}
