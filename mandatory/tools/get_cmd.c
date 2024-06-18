/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:23 by ychagri           #+#    #+#             */
/*   Updated: 2024/06/18 19:30:18 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"
#include <sys/wait.h>

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
	free(fullpath);
	if (!dirs)
		return (ft_putstr_fd("Path not found!!\n", 2), free_arr(cmd), exit(1));
	err_set = execvee(dirs, cmd);
	if (err_set == -1)
		return (ft_putstr_fd("command not found: ", 2),
			ft_putstr_fd(cmd[0], 2), ft_putstr_fd("\n", 2),
			free_arr(cmd), free_arr(dirs), exit(127));
}

void	outfile2(char **argv, char **env, int ac )
{
	int	outfile;

	outfile = open(argv[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile == -1)
		return (exit(14));
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	exec_cmds(argv[ac - 2], env);
}

void	cmd_outfile(char **argv, char **env, int ac)
{
	int		pid;
	int		status;
	int		code;

	check_files(argv, ac, OUTFILE);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork() has failed!!\n", 2), exit(1));
	if (pid == 0)
		outfile2(argv, env, ac);
	else
	{
		waitpid(pid, &status, 0);
		while (wait(NULL) != -1)
			continue ;
		if (WIFEXITED(status))
		{
			code = WEXITSTATUS(status);
			if (code)
				exit(code);
		}
	}
}

void	exec_cmds(char *argv, char **env)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (ft_strchr(cmd[0], '/') == 0)
		execution(env, cmd);
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
		{
			return (ft_putstr_fd("No such a file or directory: ", 2),
				ft_putstr_fd(cmd[0], 2), ft_putchar_fd('\n', 2),
				free_arr(cmd), exit(127));
		}
	}
}
