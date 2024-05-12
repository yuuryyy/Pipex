/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:23 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/11 19:08:20 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

void	cmd1(char **env, char **cmd)
{
	char	*path;
	char	**dirs;
	char	*fullpath;
	int		i;
	int		err_set;

	i = 0;
	fullpath = get_path(env);
	dirs = ft_split(fullpath, ':');
	free(fullpath);
	while (dirs[i])
	{
		path = ft_strjoin(dirs[i], cmd[0], '/');
		err_set = execve(path, cmd, NULL);
		free(path);
		i++;
	}
	if (err_set == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		exit(1);
	}
}

void	exec_cmd(char **argv, int *fd, char **env, int file1)
{
	char	**cmd;

	cmd = ft_split(argv[2], ' ');
	if (dup2(*fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("dup2() has failed!!\n", 2);
		exit(1);
	}
	close(0);
	if (dup2(file1, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("dup2() has failed!!\n", 2);
		exit(1);
	}
	cmd1(env, cmd);
}

void	exec_cmd2(char **argv, int *fd, char **env, int file2)
{
	char	**cmd2;

	cmd2 = ft_split(argv[3], ' ');
	if (dup2(file2, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("dup2() has failed!!\n", 2);
		exit(1);
	}
	close(0);
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("dup2() has failed!!\n", 2);
		exit(1);
	}
	cmd1(env, cmd2);
}
