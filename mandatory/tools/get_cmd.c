/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:23 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/23 12:30:18 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

int	execvee(char **dirs, char **cmd)
{
	char	*path;
	int		i;
	int		err;

	i = 0;
	while (dirs[i])
	{
		path = ft_strjoin(dirs[i], cmd[0], '/');
		err = execve(path, cmd, NULL);
		free(path);
		i++;
	}
	return (err);
}

void	execution(char **env, char **cmd)
{
	char	**dirs;
	char	*fullpath;
	int		err_set;

	fullpath = get_path(env);
	dirs = ft_split(fullpath, ':');
	if (!dirs)
	{
		free(fullpath);
		free_arr(cmd);
		exit(1);
	}
	free(fullpath);
	err_set = execvee(dirs, cmd);
	if (err_set == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		exit(1);
	}
}

void	exec_cmds(int *fd_write, char *argv, char **env)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		ft_putstr_fd("ft_split has failed ", 2);
		close(*fd_write);
		exit(1);
	}
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

void	outfile2(char *arg, char **env)
{
	char	**cmd;

	cmd = ft_split(arg, ' ');
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
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("fork() has failed!!\n", 2);
		exit(1);
	}
	if (pid == 0)
		outfile2(argv, env);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
				exit(1);
		}
	}
}
