/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:03:52 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/05 10:03:55 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
/* The isprint() function returns zero if the character tests false and
returns non-zero if the character tests true. */
{
	if (c > 31 && c < 127)
		return (1);
	else
		return (0);
}
