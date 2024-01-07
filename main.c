/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:33:56 by lumaret           #+#    #+#             */
/*   Updated: 2024/01/07 16:04:30 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	fd = open("test/test.txt", O_RDONLY);

	if (fd == -1)
	{
		write(2, "ERREUR", 6);
		return (1);
	}
	printf("line : %s",get_next_line(fd));
	printf("line : %s",get_next_line(fd));
	printf("line : %s",get_next_line(fd));
	close(fd);
	return (0);
}