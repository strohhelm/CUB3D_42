/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:40:34 by pstrohal          #+#    #+#             */
/*   Updated: 2024/09/25 17:44:22 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_line(t_map *map, int x, int y, int i)
{
	int	j;
	int	k;
	static int pl_pos = 0;

	k = ft_strlen(map->str_map[i]);
	j = -1;
	while (++j <= k)
	{
		char t = map->str_map[i][j];
		if (map->str_map[i][j] == ' ' || map->str_map[i][j] == '0' || map->str_map[i][j] == '1' || map->str_map[i][j] == 'D')
			continue ;
		else if ((map->str_map[i][j] == 'N' || map->str_map[i][j] == 'E' || map->str_map[i][j] == 'S'
				|| map->str_map[i][j] == 'W') && !pl_pos)
		{
			pl_pos++;
			map->start[2] = (int)map->str_map[i][j];
			map->str_map[i][j] = '0';
			map->start[0] = j;
			map->start[1] = i;
		}
		else if (map->str_map[i][j])
			return (printf("invalid_input\n"), 1);
	}
	return (0);
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
	err_check(arr, MALLOC);
	i = 0;
	while (i < y)
	{
		arr[i] = (int *)malloc(sizeof(int) * x);
		err_check(arr[i], MALLOC);
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
		char *str = map->str_map[y];
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


void validate_map(t_map *map)
{
	int	i;
	int	x;
	int y;

	i = -1;
	x = max_width(map->str_map, &y);
	map->map_h = y;
	map->map_w = x;
	while (map->str_map && map->str_map[++i])
	{
		if (check_line(map, x, y, i))
			exit(2);
	}
	i = -1;
	map->map = alloc_int_arr(x, y);
	fill_array(map);
	return ;
}
