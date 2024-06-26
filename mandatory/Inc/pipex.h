/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:58:53 by ychagri           #+#    #+#             */
/*   Updated: 2024/06/20 20:14:47 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../lib/Libft/libft.h"
# include <sys/wait.h>

# define INFILE 0
# define OUTFILE 1

void	exec_cmds(char *argv, char **env);
void	multipipe(char **argv, int ac, char **env);
void	here_doc(int ac, char **argv, char **env);
char	*ft_strjoin3(char *s1, char *s2);
void	cmd_outfile(char **argv, char **env, int ac);
void	execution(char **env, char **cmd);
void	check_files(char **argv, int ac, int flag);
char	*get_path(char **env);
void	free_arr(char **str);

#endif