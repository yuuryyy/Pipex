/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:24 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/25 21:28:17 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

void	open_file(int ac, char **argv, int *outfile)
{
	if (access(argv[ac - 1], F_OK) == 0)
	{
		if (access(argv[ac - 1], W_OK) == -1)
		{
			ft_putstr_fd("Permission denied: ", 2);
			ft_putstr_fd(argv[ac - 1], 2);
			ft_putchar_fd('\n', 2);
			exit (1);
		}
	}
	*outfile = open(argv[ac - 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	if (*outfile == -1)
	{
		if (ft_strchr(argv[ac - 1], '/'))
		{
			return (ft_putstr_fd("No such file or directory: ", 2),
				ft_putstr_fd(argv[ac - 1], 2), ft_putstr_fd("\n", 2), exit(1));
		}
		else
			ft_putstr_fd("open() has failed.\n", 2);
		exit(1);
	}
}

void	read_line(char *limiter, int *fd)
{
	char	*buffer;

	while (1)
	{
		write (0, "youssra_pipex> ", 16);
		buffer = get_next_line(0);
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0)
			break ;
		write (fd[1], buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(fd[1]);
}

void	child_process(int fd[2], char **argv, char **env)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	exec_cmds(argv[3], env);
}

void	last_cmd(char **argv, char **env, int ac, int *fd)
{
	int		status;
	pid_t	pid;
	int		outfile;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	open_file(ac, argv, &outfile);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork() has failed!!\n", 2), exit(1));
	if (pid == 0)
		exec_cmds(argv[4], env);
	else
	{
		waitpid(pid, &status, 0);
		while (wait(NULL) != -1)
			continue ;
		if (WIFEXITED(status))
			exit(WEXITSTATUS(status));
	}
}

void	here_doc(int ac, char **argv, char **env)
{
	pid_t	pid;
	int		fd[2][2];
	char	*limiter;

	if (pipe(fd[0]) == -1)
		return (ft_putstr_fd("pipe() has failed!!\n", 2), exit(1));
	limiter = NULL;
	limiter = ft_strjoin3(argv[2], "\n");
	read_line(limiter, fd[0]);
	free(limiter);
	dup2(fd[0][0], STDIN_FILENO);
	close(fd[0][0]);
	if (pipe(fd[1]) == -1)
		return (ft_putstr_fd("pipe() has failed!!\n", 2), exit(1));
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork() has failed!!\n", 2), exit(1));
	if (pid == 0)
		child_process(fd[1], argv, env);
	else
	{
		last_cmd(argv, env, ac, fd[1]);
	}
}
