/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:23 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/22 14:40:31 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

void	execution(char **env, char **cmd)
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

void    exec_cmds(int *fd_write, char *argv, char **env)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (dup2(*fd_write, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("dup2() has failed!!\n", 2);
		exit(1);
	}
	if (ft_strchr2(cmd[0], '/') == 0)
		execution(env, cmd);
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
		{
			ft_putstr_fd("No such a file or directory: ", 2);
			ft_putstr_fd(cmd[0], 2);
			exit(1);
		}
	}
}

void	cmd_outfile(char *argv, char **env)
{
	int		pid;
	char	**cmd;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("fork() has failed!!\n", 2);
		exit(1);	
	}
	if (pid == 0)
	{
		cmd = ft_split(argv, ' ');
		if (ft_strchr2(cmd[0], '/') == 0)
		execution(env, cmd);
		else
		{
			if (execve(cmd[0], cmd, NULL) == -1)
			{
				ft_putstr_fd("No such a file or directory: ", 2);
				ft_putstr_fd(cmd[0], 2);
				exit(1);
			}
		}
	}
	else
		waitpid(pid, NULL, 0);
}
