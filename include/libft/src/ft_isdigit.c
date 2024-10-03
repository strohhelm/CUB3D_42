/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:02:39 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/05 10:02:44 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
/* The isdigit() and isnumber() functions return zero if the character tests false and return non-zero
     if the character tests true. */
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
