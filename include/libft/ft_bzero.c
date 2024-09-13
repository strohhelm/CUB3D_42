/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:14:14 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/08 16:09:58 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n != 0)
	{
		*str = '\0';
		--n;
		if (n == 0)
			break ;
		++str;
	}
}
// int main(void)
// {
// 	char s[] = "qwefegrt";
// 	int i = 5;
// 	ft_bzero(s, i);
// 	printf("%s\n", s);
// 	return (0);
// }