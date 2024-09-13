/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:08:26 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/14 12:36:29 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters 
specified in ’set’ removed from the beginning and the end of the string.*/

char	*ft_strtrim(char const *s1, char const *set)
{
	int		strlen;
	int		start;
	int		end;

	strlen = ft_strlen(s1);
	start = 0;
	end = 0;
	if ((!*set && !*s1) || (!*s1 && *set))
		return ((char *)ft_calloc(1, 1));
	if (!*set)
		return (ft_strdup(s1));
	while ((ft_strchr(set, (int)s1[start]) != NULL) && start <= strlen)
		start++;
	if (start == strlen + 1 || !*set)
	{
		start = 0;
		strlen = 0;
	}
	else
	{
		while ((ft_strchr(set, s1[strlen - end])) != NULL)
			end++;
		end--;
	}
	return (ft_substr(s1, start, strlen - end - start));
}
	// if (start == 0 && end == 0)
	// 	return (ft_substr(s1, start, strlen + 1 - end - start));

// int main(void)
// {
// 	char s1[] = "" ;
// printf("%s$\n", ft_strtrim(s1 , ""));
// }
