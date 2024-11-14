/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:30:39 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 22:31:11 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

int	mv_arr(char **src, char **dest)
{
	int	i;

	i = 0;
	if (src && dest)
	{
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = NULL;
	}
	return (i);
}

t_game	*game_pointer(int i, void *game)
{
	static t_game	*def_not_global;

	if (i == 1 && game)
	{
		def_not_global = (t_game *)game;
		return (NULL);
	}
	else
		return (def_not_global);
}

t_uint	get_colour(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}
