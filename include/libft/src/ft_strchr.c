/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:44:43 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/31 10:43:15 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strchr() function returns a pointer to the 
first occurrence of the character c in the string s.*/

char	*ft_strchr(const char *s, int c)
{
	char			*sp;
	unsigned char	i;

	sp = (char *)s;
	i = (unsigned char)c;
	if (!sp)
		return (NULL);
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
// int main(void)
// {
// 	const char s[] = "teste";
// 	int i = 1024;
// 	printf("%s\n", ft_strchr(s, i));
// 	printf("%s\n", strchr(s, i));
// }