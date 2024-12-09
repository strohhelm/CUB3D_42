/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:20:40 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/11 20:40:17 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The memset() function writes len bytes of value c (converted to an
     unsigned char) to the string b.
 */

void	*ft_memset(void *b, int c, unsigned int n)
{
	unsigned int	i;
	unsigned char	chr;
	char			*bp;

	i = 0;
	bp = (char *)b;
	chr = (unsigned char)c;
	while (i < n)
	{
		*bp = chr;
		++bp;
		++i;
	}
	return (b);
}
/* #include <stdio.h>
#include <string.h>

int main () {
   char str[50];

   strcpy(str,"This is string.h library function");
   puts(str);

   ft_memset(str,'$',7);
   puts(str);
   
   return(0);
} */