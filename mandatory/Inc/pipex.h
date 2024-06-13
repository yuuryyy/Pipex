/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:58:53 by ychagri           #+#    #+#             */
/*   Updated: 2024/06/13 16:14:51 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../lib/Libft/libft.h"
# include <sys/wait.h>

# define INFILE 0
# define OUTFILE 1
// # define 
// # define 

void	exec_cmds(int *fd_write, char *argv, char **env);
void	multipipe(char **argv, int ac, char **env);
void	here_doc(int ac, char **argv, char **env);
void	cmd_outfile(char **argv, char *cmd, char **env, int ac);
void	execution(char **env, char **cmd);
void	check_files(char **argv, int ac, int flag, int fd);
char	*get_path(char **env);
void	free_arr(char **str);

#endif