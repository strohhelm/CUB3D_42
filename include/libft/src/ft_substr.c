/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:29:24 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/14 10:15:09 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	strlen;

	strlen = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > strlen)
		len = 0;
	else
		strlen = ft_strlen(&s[start]);
	if (strlen < len)
		len = strlen;
	substr = (char *)ft_calloc(len + 1, 1);
	if (substr == NULL)
		return (NULL);
	ft_memcpy (substr, &s[start], len);
	return (substr);
}
// int	main(void)
// {
// 	const char	*s = "";
// 	printf("%s$", ft_substr(s, 1, 1));
// 	return (0);
// }
