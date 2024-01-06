/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:50:31 by lumaret           #+#    #+#             */
/*   Updated: 2024/01/06 18:29:31 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list *stash = NULL;
	char	*line;
	int	read;

	// problemes de lecture
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0))
		return (NULL);
	read = 1;
	line = NULL;
	// read from fd and add to stash
	read_n_stash(&stash, &read);
	if (!stash)
		return (NULL);
	// extract from stash to line
	extract_line(stash, &line);
	// clean up stash and return line
	clean_stash(&stash);
	return (line);
}

void	read_n_stash(int fd, t_list **stash, int *read_ptr)
{
	char	*buff;

	while (!ft_newline(*stash) && *read_ptr != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return ;
		*read_ptr = (int)read(fd, buff, BUFFER_SIZE);
		if ((!*stash && read_ptr == 0) || read_ptr == -1)
			return (free(buff));
		buff[*read_ptr] = '\0';
		add_2_stash(stash, buff, *read_ptr);
		free(buff);
	}
}

// replay from 24:40
void	add_2_stash(t_list **stash, char *buff, int read)
{
	int	i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (read + 1));
	if (!new_node)
		return ;
	i = 0;
	while (buff[i] && i < read)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
}

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (!stash)
		return ;
	generate_line(line, stash);
	if (!*line)
		return ;
	while (stash)
	{
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;

	}
	(*line)[j] = '\0';
}