/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:32:26 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/13 12:16:19 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		slen1;
	int		slen2;

	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	joined = (char *)malloc(slen1 + slen2 + 1);
	if (joined == NULL)
		return (NULL);
	ft_memcpy(joined, (const char *)s1, slen1);
	ft_memcpy(&joined[slen1], (const char *)s2, slen2);
	joined[slen1 + slen2] = '\0';
	return (joined);
}

// int	main(void)
// {
// 	const char	*s1 = "Was soll denn das ";
// 	const char	*s2 = "bedeuten mein Herr";
// 	printf("%s", ft_strjoin(s1, s2));
// 	return (0);
// }