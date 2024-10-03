/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:08:24 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/12 18:10:07 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*actual_itoa(char *str, long n, int sign, int byte_size)
{
	long	nmod;
	int		i;

	i = byte_size - 1;
	while (n > 0)
	{
		nmod = n;
		while (nmod >= 10)
			nmod %= 10;
		str[i] = nmod + '0';
		i--;
		n /= 10;
	}
	if (sign == -1)
		str[i] = '-';
	return (str);
}

static int	calc_bs(long n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		byte_size;
	long	nb;

	nb = (long)n;
	sign = 0;
	byte_size = 0;
	if (nb < -2147483648 || nb > 2147483647)
		return (NULL);
	if (nb < 0)
	{
		sign = -1;
		byte_size += 1;
		nb *= -1;
	}
	byte_size += calc_bs(nb);
	str = (char *)ft_calloc(byte_size + 1, 1);
	if (str == NULL)
		return (NULL);
	actual_itoa(str, nb, sign, byte_size);
	if (nb == 0)
		str[byte_size - 1] = 48;
	return (str);
}

// int	main(void)
// {
// 	printf("%s$\n", ft_itoa(-2147483648));
// 	return (0);
// }