/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:47:58 by rdiary            #+#    #+#             */
/*   Updated: 2024/04/11 14:56:39 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *stack, char *buffer)
{
	char	*res;
	size_t	len;
	size_t	i;

	if (!stack)
	{
		stack = malloc(1 * sizeof(char));
		stack[0] = '\0';
	}
	if (!stack || !buffer)
		return (NULL);
	i = -1;
	len = ft_strlen(stack) + ft_strlen(buffer);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (++i < ft_strlen(stack))
		res[i] = stack[i];
	while (i < len && buffer[i - ft_strlen(stack)] != '\0')
	{
		res[i] = buffer[i - ft_strlen(stack)];
		i++;
	}
	res[i] = '\0';
	return (free(stack), res);
}

char	*ft_strchr(char *s, int c)
{
	int		i;

	if (!s)
		return (0);
	if (!c)
		return (s + ft_strlen(s));
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	return (0);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*copy;
	size_t	i;

	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i + start < ft_strlen(s) && i < len)
	{
		copy[i] = s[i + start];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
