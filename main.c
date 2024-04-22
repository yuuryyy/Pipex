/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:51:48 by ychagri           #+#    #+#             */
/*   Updated: 2024/04/14 17:49:59 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/Inc/pipex.h"

int	main()
{
    // Open a file for reading
    int file_descriptor = open("txt.txt", O_RDWR);
    if (file_descriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    // Duplicate the file descriptor and make it point to standard output
    int duplicated_descriptor = dup2(file_descriptor, 1);
    if (duplicated_descriptor == -1) {
        perror("Error duplicating file descriptor");
        return 1;
    }

    // Now, anything written to standard output will actually go to the file
    printf("This will be written to the file instead of the screen.\n");
	printf("%d     %d\n", file_descriptor, duplicated_descriptor);
    // Close the original file descriptor
    //close(file_descriptor);

    //// Close the duplicated file descriptor
    //close(duplicated_descriptor);

    return 0;

}