/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:12:05 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/11 18:32:03 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The memchr() function locates the first occurrence of c (converted to an
     unsigned char) in string s.
 */

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sp;

	sp = (unsigned char *)s;
	while (n > 0)
	{
		if (*sp == (unsigned char)c)
			return (sp);
		++sp;
		--n;
	}
	return (NULL);
}
// int main(void)
// {
// 	const char	s[] = "dzbfgnhm";
// 	printf("%s\n", ft_memchr(s, 'd', 15));
// 	printf("%s\n", memchr(s, 'd', 15));
// 	return (0);
// }