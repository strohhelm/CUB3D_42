/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:49:04 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/26 17:24:20 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	p = (char *)malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, (count * size));
	return ((void *)p);
}
// int main(void)
// {
// 	char *p;
// 	char *s;
// 	s = (char *)ft_calloc(5, 3);
// 	p = (char *)calloc(5, 3);
// 	return(0);
// 	free(p);
// 	free(s);
// }