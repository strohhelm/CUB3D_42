/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:40:34 by pstrohal          #+#    #+#             */
/*   Updated: 2024/10/01 20:54:21 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_line(t_map *map, int i)
{
	int	j;
	int	k;
	static int pl_pos = 0;

	k = ft_strlen(map->str_map[i]);
	j = -1;
	while (++j <= k)
	{
		if (map->str_map[i][j] == ' ' || map->str_map[i][j] == '0' || map->str_map[i][j] == '1')
			continue ;
		else if ((map->str_map[i][j] == 'N' || map->str_map[i][j] == 'E' || map->str_map[i][j] == 'S'
				|| map->str_map[i][j] == 'W'))
		{
			if (pl_pos)
				error_print("Are you blind?? Thats too many players");
			pl_pos++;
			map->start[2] = (int)map->str_map[i][j];
			map->str_map[i][j] = '0';
			map->start[0] = j;
			map->start[1] = i;
		}
		else if (map->str_map[i][j])
			error_print("Are you blind?? Thats not a valid map.");
	}
	return (pl_pos);
}

int	max_width(char **arr, int *y)
{
	int	max;
	int i;
	int	tmp;

	max = 0;
	i = 0;
	tmp = 0;
	if (arr)
	{
		while (arr[i])
		{
			tmp = ft_strlen(arr[i]);
			if (tmp > max)
				max = tmp;
			i++;
		}
	}
	*y = i;
	return (max);
}

int **alloc_int_arr(int x, int y)
{
	int	i;
	int	**arr;

	arr = (int **)malloc(sizeof(int *) * y);
	err_check(arr, "My god! Malloc failed, what shitshow pc is this?");
	i = 0;
	while (i < y)
	{
		arr[i] = (int *)malloc(sizeof(int) * x);
			err_check(arr[i], "My god! Malloc failed, what shitshow pc is this?");
		i++;
	}
	return (arr);
}

void fill_array(t_map *map)
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
				{
					map->map[y][x] = -1;
					x++;
				}
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
			if ((y == 0 || x == 0 || y == map->map_h || x == map->map_w) && p[y][x] == 0)
				error_print("WTF! Map not closed properly!");
			else if (p[y][x] == -1)
			{
				if (y > 0 && x > 0 && y < map->map_h - 1 && x < map->map_w - 1)
				{
					if (p[y][x + 1] == 0 || p[y][x - 1] == 0 || p[y + 1][x] == 0 || p[y - 1][x] == 0)
						error_print("WTF! Map not valid! Get those spaces away from the zeros!");
				}
			}
		}
	}
	return ;
}

void validate_map(t_map *map)
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
