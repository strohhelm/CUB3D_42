/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:46:33 by pstrohal          #+#    #+#             */
/*   Updated: 2024/05/09 20:27:49 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*jump_spaces(char *str)
{
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ' )
	{
		str++;
	}
	return (str);
}

static int	ft_detect_sign(char s)
{
	if (s == '-')
		return (-1);
	if (s == '+')
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *str)
{
	char	sign;
	char	*sp;
	long	value;

	sp = (char *)str;
	value = 0;
	sign = 0;
	sp = jump_spaces(sp);
	sign = ft_detect_sign(*sp);
	if (sign != 0)
		sp++;
	if (sign == 0)
		sign = 1;
	while (*sp)
	{
		if (*sp >= '0' && *sp <= '9')
		{
			value = value * 10;
			value = value + sign * (*sp - '0');
		}
		if (*sp < '0' || *sp > '9')
			break ;
		sp++;
	}
	return (value);
}
// #include <stdio.h>
// #include <stdlib.h>
// int main(void)
// {
// 	char a[] = "   		485335588555";
// 	long at;
// 	long atc;
// 	at = ft_atoi(a);
// 	atc = atol(a);
// 	printf("%ld\n", at);
// 	printf("%ld\n", atc);
// }
