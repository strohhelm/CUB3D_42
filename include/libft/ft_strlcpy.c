/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:27:03 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/31 10:43:27 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	size_t	src_len;

	src_len = 0;
	if (!src)
		return (0);
	while (src[src_len])
		++src_len;
	while (size > 0 && *src)
	{
		*dest++ = *src++;
		--size;
		if (size == 0)
			*(--dest) = '\0';
	}
	if (!*src)
		*(dest) = '\0';
	return (src_len);
}
// int	main(void)
// {
// 	char a[] = "sgthytjhgjty";
// 	char b[] = "oh nein";
// 	char *dest;
// 	char *src;
// 	unsigned int size = 50;
// 	dest = a;
// 	src = b;
// 	printf("%s\n", a);
// 	size = ft_strlcpy(dest, src, size);
// 	printf("%s\n", a);
// 	printf("%d", size);
// }