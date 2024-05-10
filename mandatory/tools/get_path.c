/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:58:27 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/10 00:20:34 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

char    *get_path(char **env)
{
    int i;
    char    *path = NULL;
    i = 0;
    if (!env || !*env)
        return (NULL);
    while (env[i])
    {
        if (strncmp(env[i], "PATH=", 5) == 0)
        {
             path = ft_strdup(env[i] + 5);
             break ;
        }
           
        else
            i++;
    }
    return (path);
}