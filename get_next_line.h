/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:49:08 by lumaret           #+#    #+#             */
/*   Updated: 2024/01/08 12:05:04 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# include <sys/uio.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char					*content;
	struct s_list			*next;
}				t_list;

char	*get_next_line(int fd);
void	read_n_stash(int fd, t_list **stash, int *read_ptr);
void	add_2_stash(t_list **stash, char *buff, int read);
void	extract_line(t_list *stash, char **line);
void	clean_stash(t_list **stash);
int		ft_newline(t_list *stash);
t_list	*ft_lst_get_last(t_list *stash);
void	generate_line(char **line, t_list *stash);
void	free_stash(t_list *stash);
int		ft_strlen(char *str);

#endif