/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:58:53 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/25 20:40:23 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../lib/Libft/libft.h"
# include <string.h>
# include <sys/wait.h>

// # define PIPE 0
// # define FORK 1
// # define OPEN 3
// # define DUPE2 4
// # define READ
// # define FT_SPLIT
// # define 
// # define 
// # define 
// # define 

void	exec_cmds(int *fd_write, char *argv, char **env);
void	here_doc(int ac, char **argv, char **env);
void	cmd_outfile(char *argv, char **env);
void	execution(char **env, char **cmd);
void	check_files(char **argv, int ac);
char	*get_path(char **env);
void	free_arr(char **str);

#endif