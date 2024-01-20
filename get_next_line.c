/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtolin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:51:08 by jtolin            #+#    #+#             */
/*   Updated: 2024/01/18 14:51:11 by jtolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


char	*get_next_line(int fd)
{
	int		ret;
	char	*line;
	char	buffer[BUFFER_SIZE + 1];

	ret = 1;
	line = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	while (ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);

		if (ret == -1)
		{
			free(line);
			return (NULL);
		}

		buffer[ret] = '\0';

		if (line == NULL)
			line = ft_strdup(buffer);
		else
		{
			char *tmp = ft_strjoin(line, buffer);
			free(line);
			line = tmp;
		}

		// Check for newline in buffer
		char *newline_pos = ft_strchr(buffer, '\n');

		// If a newline is found, move the file descriptor to the beginning of the next line
		if (newline_pos != NULL)
		{
			// Include the newline character in the line
			size_t line_length = newline_pos - buffer + 1;

			// Check if the line is empty or not
			if (line_length > 1)
			{
				char *tmp = ft_substr(line, 0, ft_strlen(line) - 1);
				free(line);
				line = tmp;
			}

			lseek(fd, line_length - ret, SEEK_CUR);
			break;
		}

		// Check for consecutive newlines
		if (ret == 0 && ft_strchr(line, '\n') == NULL)
		{
			// Check if the line is empty or not
			if (line[0] != '\0')
				break;
		}
	}

	// Check if the end of the file is reached without reading data
	if (ret == 0 && (line == NULL || line[0] == '\0'))
	{
		free(line);
		return (NULL);
	}

	return (line);
}

/*int main (int ac, char **av)
{
	int fd;
	char *line;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		line = get_next_line(fd);
			printf("%s\n", line);
	}
	return (0);
}
*/