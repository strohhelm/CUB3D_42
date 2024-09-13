/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:29:58 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/06 15:40:31 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1p;
	unsigned char	*s2p;

	s1p = (unsigned char *)s1;
	s2p = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 1 && *s1p)
	{
		if (*s1p == *s2p)
		{
			s1p++;
			s2p++;
			n--;
		}
		else
			break ;
	}
	return (*s1p - *s2p);
}
// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char a[] = "ipsum";
// 	char b[] = "ipsumm";
// 	char *aa = a;
// 	char *bb = b;
// 	size_t n = 10;
// 	printf("%d\n", ft_strncmp(aa, bb, n));
// 	printf("%d\n", strncmp(aa, bb, n));
// }
