/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_doors_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:53:03 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 15:17:30 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

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
		error_print("Oh, that aint a great place for a door there!");
}
