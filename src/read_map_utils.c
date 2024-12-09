/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:42:51 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/27 12:02:56 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	fill_array(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->map_h)
	{
		x = -1;
		while (++x < map->map_w)
		{
			if (!map->str_map[y][x])
			{
				while (x < map->map_w)
					map->map[y][x++] = -1;
				break ;
			}
			if (map->str_map[y][x] == ' ')
				map->map[y][x] = -1;
			else if (map->str_map[y][x] == '1')
				map->map[y][x] = 1;
			else if (map->str_map[y][x] == '0' || map->str_map[y][x] == 'D')
				map->map[y][x] = 0;
		}
	}
}

void	check_map_middle(int **p, int x, int y)
{
	if (p[y][x + 1] == 0 || p[y][x - 1] == 0 || p[y + 1][x] == 0 || p[y
		- 1][x] == 0)
		error_print("WTF! Map not valid!");
	return ;
}

void	validate_int_map(t_map *map)
{
	int	y;
	int	x;
	int	**p;

	y = -1;
	p = map->map;
	while (++y < map->map_h)
	{
		x = -1;
		while (++x < map->map_w)
		{
			if ((y == 0 || x == 0 || y == map->map_h - 1 || x == map->map_w - 1)
				&& p[y][x] == 0)
				error_print("WTF! Map not closed properly!");
			else if (p[y][x] == -1)
			{
				if (y > 0 && x > 0 && y < map->map_h - 1 && x < map->map_w - 1)
					check_map_middle(p, x, y);
			}
		}
	}
	return ;
}

void	validate_map(t_map *map)
{
	int	i;
	int	x;
	int	y;
	int	check;
	int	tmp;

	i = -1;
	x = max_width(map->str_map, &y);
	map->map_h = y;
	map->map_w = x;
	check = 0;
	while (map->str_map && map->str_map[++i])
	{
		tmp = check_line(map, i);
		if (tmp == 1)
			check++;
	}
	if (!check)
		error_print("Can't you see? No Player found anywhere!");
	i = -1;
	map->map = alloc_int_arr(x, y);
	fill_array(map);
	validate_int_map(map);
	return ;
}
