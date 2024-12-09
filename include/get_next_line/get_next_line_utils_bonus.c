/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:53:09 by pstrohal          #+#    #+#             */
/*   Updated: 2024/05/22 16:32:19 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char			*sp;
	unsigned char	i;

	sp = (char *)s;
	i = (unsigned char)c;
	if (*sp == c)
		return (sp);
	while (*sp)
	{
		if (*sp == i)
			return (sp);
		++sp;
		if (*sp == '\0' && i == '\0')
			return (sp);
	}
	return (NULL);
}

char	*ft_strjoin1(char *s1, char const *s2)
{
	char	*joined;
	int		slen1;
	int		slen2;

	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	joined = (char *)malloc(slen1 + slen2 + 1);
	if (!joined)
		return (free(s1), NULL);
	ft_memcpy(joined, (const char *)s1, slen1);
	ft_memcpy(&joined[slen1], (const char *)s2, slen2);
	joined[slen1 + slen2] = '\0';
	free(s1);
	return (joined);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*source;
	char		*destin;
	size_t		i;

	if (!dst && !src)
		return (dst);
	source = (const char *)src;
	destin = (char *)dst;
	i = 0;
	while (i < n && src)
	{
		destin[i] = source[i];
		i++;
	}
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

// void	ft_bzero(void *s, size_t n)
// {
// 	char	*str;

// 	str = (char *)s;
// 	while (n != 0)
// 	{
// 		*str = '\0';
// 		--n;
// 		if (n == 0)
// 			break ;
// 		++str;
// 	}
// }
