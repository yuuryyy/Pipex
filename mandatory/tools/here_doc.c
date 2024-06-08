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
		if (strchr(argv[ac - 1], '/'))
		{
			return (ft_putstr_fd("No such file or directory: ", 2),
				ft_putstr_fd(argv[ac - 1], 2), ft_putstr_fd("\n", 2), exit(1));
		}
		else
			ft_putstr_fd("open() has failed.\n", 2);
		exit(1);
	}
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

void	read_line(char *limiter, int *fd)
{
	char	c[2];
	char	*buffer;
	int		read_bytes;

	while (1)
	{
		buffer = NULL;
		read_bytes = read(0, c, 1);
		while (*c && read_bytes == 1 && *c != '\n' )
		{
			c[1] = '\0';
			buffer = ft_strjoin2(buffer, c);
			read_bytes = read(0, c, 1);
		}
		if (read_bytes == -1)
			return (ft_putstr_fd("read() has failed!!\n", 2), exit(1));
		if (*c == '\n')
			buffer = ft_strjoin2(buffer, "\n");
		if (ft_strncmp(buffer, limiter, strlen(limiter)) == 0)
			break ;
		write (fd[1], buffer, ft_strlen(buffer));
	}
	free(limiter);
	free(buffer);
}

void	child_process(int fd[2][2], char **argv, char **env)
{
	char	*limiter;

	close(fd[0][0]);
	limiter = ft_strjoin2(argv[2], "\n");
	if (pipe(fd[1]) == -1)
		return (ft_putstr_fd("pipe() has failed!!\n", 2), exit(1));
	read_line(limiter, fd[1]);
	if (dup2(fd[1][0], STDIN_FILENO) == -1)
		return (ft_putstr_fd("dup2() has failed!!\n", 2), exit(1));
	close(fd[1][1]);
	exec_cmds(&fd[0][1], argv[3], env);
}

void	here_doc(int ac, char **argv, char **env)
{
	pid_t	pid;
	int		outfile;
	int		fd[2][2];

	open_file(ac, argv, &outfile);
	if (pipe(fd[0]) == -1)
		return (ft_putstr_fd("pipe() has failed!!\n", 2), exit(1));
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork() has failed!!\n", 2), exit(1));
	if (pid == 0)
		child_process(fd, argv, env);
	else
	{
		close(fd[0][1]);
		wait(NULL);
		if (dup2(fd[0][0], STDIN_FILENO) == -1)
			return (ft_putstr_fd("dup2() has failed!!\n", 2), exit(1));
		exec_cmds(&outfile, argv[4], env);
	}
}
