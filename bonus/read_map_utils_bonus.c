/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:42:51 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/13 17:41:05 by timschmi         ###   ########.fr       */
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
	if (p[y][x + 1] == 0 || p[y][x - 1] == 0 || p[y + 1][x] == 0 || p[y
		- 1][x] == 0)
		error_print("WTF! Map not valid! Get those \
			spaces away from the zeros!");
	return ;
}

void	init_rest_door(t_door *dp, t_da *hlp, int lr)
{
	dp->id = hlp->id;
	dp->map_x = hlp->x;
	dp->map_y = hlp->y;
	dp->status = CLOSED;
	dp->progress = 0;
	if (lr)
		dp->texture = mlx_load_png("./include/textures/gate_right.png");
	else
		dp->texture = mlx_load_png("./include/textures/gate_left.png");
	if (!dp->texture)
		error_print("not a valid path to door texture you idiot!");
}

void	init_left_door_north(t_door *dp, t_da *hlp)
{
	dp->p1.x = hlp->x + 0.5;
	dp->p1.y = hlp->y + 0.5;
	dp->p2.x = hlp->x + 0.5;
	dp->p2.y = hlp->y;
	init_rest_door(dp, hlp, 0);
}
void	init_right_door_north(t_door *dp, t_da *hlp)
{
	dp->p2.x = hlp->x + 0.5;
	dp->p2.y = hlp->y + 1.0;
	dp->p1.x = hlp->x + 0.5;
	dp->p1.y = hlp->y + 0.5;
	init_rest_door(dp, hlp, 1);
}

void	init_left_door_west(t_door *dp, t_da *hlp)
{
	dp->p1.x = hlp->x;
	dp->p1.y = hlp->y + 0.5;
	dp->p2.x = hlp->x + 0.5;
	dp->p2.y = hlp->y + 0.5;
	init_rest_door(dp, hlp, 0);
}
void	init_right_door_west(t_door *dp, t_da *hlp)
{
	dp->p2.x = hlp->x + 0.5;
	dp->p2.y = hlp->y + 0.5;
	dp->p1.x = hlp->x + 1.0;
	dp->p1.y = hlp->y + 0.5;
	init_rest_door(dp, hlp, 1);
}

t_door	*make_new_door(t_da *hlp, int lr)
{
	t_door	*dp;

	dp = (t_door *)malloc(sizeof(t_door));
	if (!dp)
		error_print("thats too bad bro, malloc fucked up!");
	if (hlp->dir == NORTH && lr == 0)
		init_left_door_north(dp, hlp);
	else if (hlp->dir == NORTH && lr == 1)
		init_right_door_north(dp, hlp);
	else if (hlp->dir == WEST && lr == 0)
		init_left_door_west(dp, hlp);
	else if (hlp->dir == WEST && lr == 1)
		init_right_door_west(dp, hlp);
	return (dp);
}

void	insert_door(t_doorstuff *d, int dir, int x, int y)
{
	t_door	*tmp;
	t_list	*new_node;
	t_da	hlp;
	int		i;

	hlp.dir = dir;
	hlp.x = x;
	hlp.y = y;
	i = -1;
	while (++i < 2)
	{
		hlp.id = d->nb;
		tmp = make_new_door(&hlp, i);
		new_node = ft_lstnew((void *)tmp);
		if (!new_node)
			error_print("fuckk off malloc stupid!");
		ft_lstadd_back(&d->doors, new_node);
		d->nb++;
	}
}
void	check_door(t_doorstuff *d, int **p, int x, int y)
{
	if (p[y][x + 1] == 0 && p[y][x - 1] == 0 && p[y - 1][x] == 1 && p[y
		+ 1][x] == 1)
		return (insert_door(d, NORTH, x, y));
	else if (p[y][x + 1] == 1 && p[y][x - 1] == 1 && p[y - 1][x] == 0 && p[y
		+ 1][x] == 0)
		return (insert_door(d, WEST, x, y));
	else
		error_print("Oh my god that aint a fukin great place for a door there!");
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
			if (p[y][x] == 2)
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
