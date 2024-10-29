/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:42:51 by pstrohal          #+#    #+#             */
/*   Updated: 2024/10/28 15:14:06 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

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
			else if (map->str_map[y][x] == '0')
				map->map[y][x] = 0;
			else if (map->str_map[y][x] == 'D')
				map->map[y][x] = 2;
		}
	}
}

void	check_map_middle(int **p, int x, int y)
{
	if (p[y][x + 1] == 0 || p[y][x - 1] == 0
		|| p[y + 1][x] == 0 || p[y - 1][x] == 0)
		error_print("WTF! Map not valid! Get those \
			spaces away from the zeros!");
	return ;
}

t_door	*make_new_door(int dir, int x, int y)
{
	t_door	*dp;

	dp = (t_door *)malloc(sizeof(t_door));
	if (!dp)
		error_print("thats too bad bro, malloc fucked up!");
	dp->left.x = x;
	dp->left.y = y + y + 0.5;
	dp->right.x = x + 1;
	dp->right.y = y + 0.5;
	if (dir == NORTH)
	{
		dp->left.x = x + 0.5;
		dp->left.y = y + 1;
		dp->right.x = x + 0.5;
		dp->right.y = y;
	}
	dp->status = CLOSED;
	dp->progress = 0;
	dp->texture = mlx_load_png("./include/textures/door.png");
	if (!dp->texture)
		error_print("not a valid path to door texture you idiot!");
	return (dp);
}

void	insert_door(t_doorstuff *d, int dir, int x, int y)
{
	t_door *tmp;
	t_list	*new_node;
	
	tmp = make_new_door(dir, x, y);
	new_node = ft_lstnew((void *) tmp);
	if (!new_node)
		error_print("fuckk off malloc stupid!");
	ft_lstadd_back(&d->doors, new_node);
	d->nb++;
}
void	check_door(t_doorstuff *d, int **p, int x, int y)
{
	if (p[y][x + 1] == 0 && p[y][x - 1] == 0
		&& p[y - 1][x] == 1 && p[y + 1][x] == 1)
		return (insert_door(d, NORTH, x, y));
	else if (p[y][x + 1] == 1 && p[y][x - 1] == 1
		&& p[y - 1][x] == 0 && p[y + 1][x] == 0)
		return (insert_door(d, WEST, x, y));
	else
		error_print("Oh mah gaawhd that aint a fukin great place for a door there ,is it?");
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
			if ((y == 0 || x == 0 || y == map->map_h || x == map->map_w)
				&& p[y][x] == 0)
				error_print("WTF! Map not closed properly!");
			else if (p[y][x] == -1)
			{
				if (y > 0 && x > 0 && y < map->map_h - 1 && x < map->map_w - 1)
					check_map_middle(p, x, y);
			}
			if (p[y][x]== 2)
				check_door(&map->dstuff, p, x, y);
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
