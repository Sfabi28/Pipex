/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:51:13 by sfabi             #+#    #+#             */
/*   Updated: 2024/04/26 15:21:58 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	fd[2];

	i = 1;
	if (argc < 5)
		return (perror("Error!\ntoo few arguments"), 1);
	fd[0] = 1;
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) && i++)
		fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		ft_heredoc(argv);
	else
	{
		fd[0] = open(argv[1], O_RDONLY, 0777);
		fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd[0], 0);
	}
	if (fd[0] < 0 || (fd[1] < 0 && close(fd[0])))
		ft_perror("Error!\nfile opening failed");
	while (++i < argc - 2)
		child(argv[i], env);
	dup2(fd[1], 1);
	if (command(argv[argc - 2], env))
		return (perror("Error!\nExecve fail"), !(close(fd[0]) + close(fd[1])));
	return (close(fd[0]) + close(fd[1]));
}

void	child(char *argv, char **env)
{
	int	pid;
	int	arr[2];

	if (pipe(arr) < 0)
		ft_perror("Error!\nerror during pipe creation");
	pid = fork();
	if (pid < 0 && !(close(arr[0]) + close(arr[1])))
		ft_perror("Error!\nFork execution failed");
	if (pid == 0)
	{
		close(arr[0]);
		dup2(arr[1], 1);
		if (command(argv, env))
			ft_perror("Error!\nexecve failed");
	}
	else
	{
		close(arr[1]);
		dup2(arr[0], 0);
		waitpid(pid, NULL, 0);
	}
}

int	command(char *argv, char **env)
{
	char	*path;
	char	**split_cmd;

	split_cmd = ft_split(argv, ' ');
	if (!split_cmd)
		ft_perror("Error!\nerror in split creation");
	path = get_path(split_cmd[0], env);
	if (path == NULL && free_split(split_cmd))
		ft_perror("Error\nerror while trying to get path");
	if (execve(path, split_cmd, env) < 0)
		return (free_split(split_cmd));
	return (0);
}

void	ft_heredoc(char **argv)
{
	char	*line;
	int		arr[2];
	int		pid;

	if (pipe(arr) < 0)
		ft_perror("Error!\nerror during pipe creation");
	pid = fork();
	if (pid < 0)
		ft_perror("Error!\nFork execution failed");
	if (pid == 0 && !close(arr[0]))
	{
		while (write(1, "pipe heredoc> ", 14) && read_gnl(&line))
		{
			if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0
				&& line[ft_strlen(argv[2])] == '\n')
				exit(close(arr[1]) + ft_free(line));
			write(arr[1], line, ft_strlen(line));
			free(line);
		}
	}
	else
	{
		dup2(arr[0], close(arr[1]));
		wait(NULL);
	}
}
