/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:56:24 by sfabi             #+#    #+#             */
/*   Updated: 2024/02/19 10:21:55 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	arr[2];
	int	pid;
	int	fds[2];

	if (argc != 5)
		return (perror("Error!\nwrong number of arguments"), 1);
	if (pipe(arr) < 0)
		return (perror("Error!\nerror in pipe creation"), 1);
	fds[0] = open(argv[1], O_RDONLY, 0777);
	fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fds[0] < 0 || (fds[1] < 0 && close(fds[0])))
		ft_perror("Error!\nfile opening failed");
	pid = fork();
	if (pid < 0 && !(close(fds[0]) + close(fds[1])))
		return (perror("Error!\nerror in child creation"), 1);
	if (pid == 0)
		child(fds[0], argv, env, arr);
	else
	{
		waitpid(pid, NULL, WNOHANG);
		child2(fds[1], argv, env, arr);
	}
	return (close(fds[0]) + close(fds[1]) + close(arr[0]) + close(arr[1]));
}

void	child(int fds, char **argv, char **env, int arr[2])
{
	char	*path;
	char	**split_cmd;

	close(arr[0]);
	split_cmd = ft_split(argv[2], ' ');
	if (!split_cmd && !(close(fds) + close(arr[1])))
		ft_perror("Error!\nerror in split creation");
	path = get_path(split_cmd[0], env);
	if (path == NULL && (free_split(split_cmd) + close(fds) + close(arr[1])))
		ft_perror("Error\nerror while trying to get path");
	dup2(arr[1], 1);
	close(arr[1]);
	dup2(fds, 0);
	close(fds);
	if (execve(path, split_cmd, env) < 0)
	{
		free_split(split_cmd);
		ft_perror("Error!\nerror during execution");
	}
	free(path);
	free_split(split_cmd);
}

void	child2(int fds, char **argv, char **env, int arr[2])
{
	char	*path;
	char	**split_cmd;

	close(arr[1]);
	split_cmd = ft_split(argv[3], ' ');
	if (!split_cmd && !(close(fds) + close(arr[0])))
		ft_perror("Error!\nerror in split creation");
	path = get_path(split_cmd[0], env);
	if (path == NULL && (free_split(split_cmd) + close(fds) + close(arr[0])))
		ft_perror("Error\nerror while trying to get path");
	dup2(arr[0], 0);
	close(arr[0]);
	dup2(fds, 1);
	close(fds);
	if (execve(path, split_cmd, env) < 0 && free_split(split_cmd))
		ft_perror("Error!\nerror during execution");
	free(path);
	free_split(split_cmd);
}
