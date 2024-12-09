/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:40:34 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/27 12:02:25 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

bool	check_char(char c)
{
	if (c == ' ' || c == '0' || c == '1')
		return (true);
	return (false);
}

bool	check_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

int	check_line(t_map *map, int i)
{
	int			j;
	int			k;
	static int	pl_pos = 0;

	k = ft_strlen(map->str_map[i]);
	j = -1;
	while (++j <= k)
	{
		if (check_char(map->str_map[i][j]))
			continue ;
		else if (check_player(map->str_map[i][j]))
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
	int	i;
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

int	**alloc_int_arr(int x, int y)
{
	int	i;
	int	**arr;

	arr = (int **)malloc(sizeof(int *) * y);
	err_check(arr, "My god! Malloc failed, what shitshow pc is this?");
	i = 0;
	while (i < y)
	{
		arr[i] = (int *)malloc(sizeof(int) * x);
		err_check(arr[i], "My god! Malloc failed, what shitty pc is this?");
		i++;
	}
	return (arr);
}
