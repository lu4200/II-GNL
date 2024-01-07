/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumaret <lumaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:50:31 by lumaret           #+#    #+#             */
/*   Updated: 2024/01/07 16:09:06 by lumaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//principal fonction w/ 3 big steps
char	*get_next_line(int fd)
{
	static t_list *stash = NULL;
	char	*line;
	int	readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	readed = 1;
	line = NULL;
	// read from fd and add to stash
	read_n_stash(fd, &stash, &readed);
	if (!stash)
		return (NULL);
	// extract from stash to line
	extract_line(stash, &line);
	// clean up stash and return line
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

//take in buffer the char read, put in the stash + free buff
void	read_n_stash(int fd, t_list **stash, int *read_ptr)
{
	char	*buff;

	while (!ft_newline(*stash) && *read_ptr != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return ;
		*read_ptr = (int)read(fd, buff, BUFFER_SIZE);
		if ((!*stash && read_ptr == 0) || *read_ptr == -1)
			return (free(buff));
		buff[*read_ptr] = '\0';
		add_2_stash(stash, buff, *read_ptr);
		free(buff);
	}
}

// new node of t_list in stash
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
	if (!new_node->content)
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

// copy content of stash to line until meeting '\n'
void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (!stash)
		return ;
	generate_line(line, stash);
	if (!*line)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
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

//
void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int	i;
	int	j;

	clean_node = malloc(sizeof(t_list));
	if (!stash || !clean_node)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * (ft_strlen(last->content) - i) + 1);
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}