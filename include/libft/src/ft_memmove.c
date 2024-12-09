/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:02:53 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/11 16:27:59 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	c;

	if (!dst && !src)
		return (dst);
	s = (char *)src;
	d = (char *)dst;
	c = 0;
	if (d < s)
	{
		while (c < n)
		{
			d[c] = s[c];
			c++;
		}
	}
	while (c < n)
	{
		d[n - 1 - c] = s[n - 1 - c];
		c++;
	}
	return (dst);
}
// int main(void)
// {
// 	const char	s[] = "123456789";
// 	char		d[] = "123456789";

// 	printf("%s", ft_memmove(d, d+3, 5));
// }