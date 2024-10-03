/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:03:23 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/11 19:26:12 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)

{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/* The functions return zero if the character tests false and return non-zero 
if the character tests 
true. */