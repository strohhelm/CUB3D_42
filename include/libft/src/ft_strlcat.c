/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:28:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/13 20:44:09 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	catlen;
	unsigned int	destlen;
	unsigned int	srclen;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dest);
	catlen = size - destlen - 1;
	if (destlen >= size)
		return (srclen + size);
	if (catlen > srclen)
		catlen = srclen;
	if (catlen > 0)
		ft_strlcpy(&dest[destlen], (char *)src, catlen + 1);
	return (destlen + srclen);
}
// int	main(void)
// {
// 	char a[10] = "a";
// 	char b[] = "lorem ipsum dolor sit amet";
// 	size_t size = 0;

// 	printf("%s\n", a);
// 	printf("%zu\n", ft_strlcat(a, b, size));
// 	printf("%s$\n", a);
// }