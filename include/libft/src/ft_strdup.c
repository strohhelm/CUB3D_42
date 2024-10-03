/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:59:22 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/13 18:47:32 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strdup() function allocates sufficient memory for a copy of the
     string s1, does the copy, and returns a pointer to it.  The pointer may
     subsequently be used as an argument to the function free(3).

     If insufficient memory is available, NULL is returned and errno is set to
     ENOMEM.*/

char	*ft_strdup(const char *s1)
{
	char	*s1p;
	char	*s2p;
	size_t	strlen;

	s1p = (char *) s1;
	strlen = ft_strlen(s1p) + 1;
	s2p = (char *)malloc(strlen);
	if (s2p == NULL)
	{
		return (NULL);
		errno = ENOMEM;
	}
	ft_strlcpy(s2p, s1p, strlen);
	return (s2p);
}
// int	main(void)
// {
// 	char *s = "4563544bv ";
// 	printf("%s", ft_strdup(s));
// 	return (0);
// }