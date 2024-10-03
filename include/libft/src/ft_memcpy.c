/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:28:54 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/13 20:09:41 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*The memcpy() function copies n bytes from memory area src to memory area
     dst.  If dst and src overlap, behavior is undefined.  Applications in
     which dst and src might overlap should use memmove(3) instead.*/

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
	while (i < n)
	{
		destin[i] = source[i];
		i++;
	}
	return (dst);
}
// int main(void)
// {
// 	const char	s[] = "Bz@|Ly!8OE,^r5F}r'78;f[WMuF-N]'2Ucp\%6q";
// 	char		d[] = "aewrfghjt434t54i78t54r5jiklo;9liktgrf56jrttbtyuikl9op;";

// 	printf("%s", memcpy(d, s, 40));
// }
