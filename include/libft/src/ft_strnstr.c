/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:34:56 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/13 15:16:38 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hay;
	char	*nee;
	size_t	neelen;

	hay = (char *)haystack;
	nee = (char *)needle;
	neelen = ft_strlen(nee);
	if (!*nee)
		return (hay);
	while (len > 0 && *hay)
	{
		if (*hay == *nee)
		{
			if (len >= neelen && (ft_strncmp(hay, nee, neelen) == 0))
				return (hay);
		}
		++hay;
		--len;
	}
	return (NULL);
}

// int	main(void)
// {
// 	// char a[] = "lorem ipsum dolor sit amet";
// 	// char b[] = "ipsumm";
// 	// size_t	len = 15;
// 	printf("%s\n", ft_strnstr("MZIRIBMZIRIBMZE123", "MZIRIBMZE", 9));
// 	// printf("%s\n", strnstr(a, b, len));
// 	return (0);
// }