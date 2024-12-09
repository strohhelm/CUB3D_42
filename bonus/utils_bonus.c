/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:30:39 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/15 17:02:45 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// returns the length od a string array
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

// copies an array of strings from src to dest
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

// returns the game pointer if hard to access
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

// checks which side the point p is on when you look from a to b
int	left_or_right(t_point a, t_point b, t_point p)
{
	double	cross_product;
	t_point	b_vector;
	t_point	p_vector;

	b_vector = vector(a, b);
	p_vector = vector(a, p);
	cross_product = b_vector.x * p_vector.y - b_vector.y * p_vector.x;
	if (cross_product < 0)
		return (LEFT);
	else
		return (RIGHT);
}

int	numbers(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit((int)*str))
			return (0);
		str++;
	}
	return (1);
}
