/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:40:34 by pstrohal          #+#    #+#             */
/*   Updated: 2024/09/15 16:40:50 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// int	check_line(char **map, int x, int y, int i)
// {
// 	int	j;
// 	int	k;

// 	k = ft_strlen(map[i]);
// 	j = -1;
// 	while (++j <= k)
// 	{
// 		if (map[i][j] == ' ' || map[i][j] == '0', || map[i][j] == '1')
// 			check_char(str_map)
// 	}
// }

int	max_width(char **arr, int *y)
{
	int	max;
	int	tmp;

	max = 0;
	*y = 0;
	tmp = 0;
	if (arr)
	{
		while (arr[*y])
		{
			tmp = ft_strlen(arr[*y]);
			if (tmp > max)
				max = tmp;
			*y++;
		}
	}
	return (max);
}

void read_map(t_map *map, char **str_map)
{
	int	i;
	int	x;
	int y;

	i = -1;
	x = max_width(str_map, &y);
	map->map_h = y;
	map->map_w = x;
	while (str_map && str_map[++i])
	{
		if (check_line(str_map, x, y, i))
			exit(2);
	}
	return ;
}