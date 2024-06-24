/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:47:30 by rdiary            #+#    #+#             */
/*   Updated: 2024/06/24 14:16:55 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_line(int fd, char *stack)
{
	int		r;
	char	*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	r = 1;
	while (r != 0 && !ft_strchr(stack, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[r] = '\0';
		stack = ft_strjoin(stack, buff);
	}
	free(buff);
	return (stack);
}

char	*ft_get_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_substr(str, 0, i + 1);
	return (line);
}

char	*ft_get_rest(char *str)
{
	char	*stack;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	stack = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
	free(str);
	return (stack);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stack[1024];

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	stack[fd] = ft_read_line(fd, stack[fd]);
	if (!stack[fd])
		return (NULL);
	line = ft_get_line(stack[fd]);
	stack[fd] = ft_get_rest(stack[fd]);
	return (line);
}
