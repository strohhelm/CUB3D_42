/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:16:48 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/11 19:28:09 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The memcmp() function compares byte string s1 against byte string s2.
// Both strings are assumed to be n bytes long.

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sp1;
	unsigned char	*sp2;

	sp1 = (unsigned char *)s1;
	sp2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 1)
	{
		if (*sp1 == *sp2)
		{
			sp1++;
			sp2++;
			n--;
		}
		else
			break ;
	}
	return (*sp1 - *sp2);
}

// int	main(void)
// {
// 	char a[] = "ghhjm";
// 	char b[] = "ghtyhjm";
// 	char *aa = a;
// 	char *bb = b;
// 	unsigned int n = 6;
// 	printf("%d\n", ft_memcmp(aa, bb, n));
// 	printf("%d\n", memcmp(aa, bb, n));
// }