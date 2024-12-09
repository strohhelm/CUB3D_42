/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:14:00 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/13 15:24:52 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*sp;
	char			*tp;
	unsigned char	chr;

	sp = (char *)s;
	tp = NULL;
	chr = (unsigned char)c;
	while (*sp)
	{
		if (*sp == chr)
			tp = sp;
		++sp;
		if (!*sp && chr == 0)
			return (sp);
	}
	if (*sp == 0 && chr == 0)
		return (sp);
	return (tp);
}
// int main(void)
// {
// 	const char s[] = "teste";
// 	int i = 'e';
// 	printf("%s\n", ft_strrchr(s, i));
// 	printf("%s\n", strrchr(s, i));
// }